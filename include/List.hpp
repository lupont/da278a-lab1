#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cassert>
#include <iterator>
#include <stdlib.h>
#include <type_traits>

#define CHECK assert(Invariant());

template<class T>
class List {
    /* Forward Declarations */
    class Node;

private:
    class Link {
        friend class List<T>;
        Link* _next;
        Link* _prev;

        Link() : _next(this), _prev(this) {}

    public:
        void insert_after(Node* toInsert)
        {
            toInsert->_prev = this;
            toInsert->_next = _next;
            _next->_prev = toInsert;
            _next = toInsert;
        }

        void insert_before(Node* toInsert)
        {
            toInsert->_prev = _prev;
            toInsert->_next = this;
            _prev->_next = toInsert;
            _prev = toInsert;
        }

        Node* delete_after()
        {
            Link* tmp = _next;
            _next = _next->_next;
            _next->_prev = _prev;
            return static_cast<Node*>(tmp);
        }

        Node* delete_before()
        {
            Link* tmp = _prev;
            _prev->_prev->_next = this;
            _prev = _prev->_prev;
            return static_cast<Node*>(tmp);
        }
    };

    class Node : public Link {
        friend class List;
        T _data;

    public:
        Node(const T& data) : _data(data) {}
    };

    /* class ListIter */
    template<class X>
    class ListIter {
        friend class List<T>;

        Node* _ptr;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using reference         = X&;
        using pointer           = X*;

        ListIter(const Link* p) : _ptr(static_cast<Node*>(const_cast<Link*>(p))) {}
        ListIter() = default;

        template<class Y, class = std::enable_if<!std::is_const<Y>::value>>
        ListIter(const ListIter<Y>& other) { _ptr = other._ptr; }
        ListIter(const ListIter<X>& other) { _ptr = other._ptr; }

        ~ListIter() = default;

        ListIter& operator=(const ListIter<X>& other)
        {
            if (&other == this)
                return *this;

            _ptr = other._ptr;
            return *this;
        }

        X& operator*()  { return  _ptr->_data; }
        X* operator->() { return &_ptr->_data; }

        ListIter<X>& operator++()
        {
            _ptr = static_cast<Node*>(_ptr->_next);
            return *this;
        }

        ListIter<X> operator++(int)
        {
            auto tmp(*this);
            operator++();
            return tmp;
        }

        ListIter<X>& operator--()
        {
            _ptr = static_cast<Node*>(_ptr->_prev);
            return *this;
        }

        ListIter<X> operator--(int)
        {
            auto temp(*this);
            operator--();
            return temp;
        }

        friend bool operator ==(const ListIter& lhs, const ListIter& rhs)
        {
            return lhs._ptr == rhs._ptr;
        }

        friend bool operator !=(const ListIter& lhs, const ListIter& rhs)
        {
            return !(lhs == rhs);
        }
    };

    /* List methods */

    Link _head;

public:
    using iterator = ListIter<T>;
    using const_iterator = ListIter<const T>;

    List() = default;

    List(const List& other) : List()
    {
        for (const_iterator it = other.cbegin(); it != other.cend(); ++it)
            push_back(*it);
        CHECK
    }

    List(const char* str) : List()
    {
        const char* ptr = str;

        while (*ptr != '\0')
            push_back(*ptr++);

        CHECK
    }

    ~List() {
        Link* link = &_head;
        while ((link = link->_next) != &_head)
            delete link;
    }

    List& operator=(const List& other)
    {
        if (&other == this)
            return *this;

        for (auto it = other.begin(); it != other.end(); ++it)
            push_back(*it);
        CHECK
    }

          T& front()       { return static_cast<Node*>(_head._next)->_data; }
    const T& front() const { return static_cast<Node*>(_head._next)->_data; }

          T& back()        { return static_cast<Node*>(_head._prev)->_data; }
    const T& back()  const { return static_cast<Node*>(_head._prev)->_data; }

    iterator       begin()        noexcept { return iterator(_head._next);       }
    const_iterator begin()  const noexcept { return const_iterator(_head._next); }
    const_iterator cbegin() const noexcept { return const_iterator(_head._next); }

    iterator       end()        noexcept { return iterator(&_head);       }
    const_iterator end()  const noexcept { return const_iterator(&_head); }
    const_iterator cend() const noexcept { return const_iterator(&_head); }

    bool empty() const noexcept { return cbegin() == cend(); }

    size_t size() const noexcept { return std::distance(begin(), end()); }

    size_t Count() const noexcept
    {
        const Link* link = &_head;
        size_t length = 0;

        while ((link = link->_next) != &_head)
            length++;

        return length;
    }

    void push_back (const T& value) { _head.insert_before(new Node(value)); CHECK }
    void push_front(const T& value) { _head.insert_after (new Node(value)); CHECK }

    void pop_back()  { delete (_head.delete_before()); CHECK }
    void pop_front() { delete (_head.delete_after ()); CHECK }

    void pop_all()
    {
        while (_head._next != &_head)
            pop_front();
        CHECK
    }

    void swap(List<T>& rhs)
    {
        Link* next = _head._next;
        Link* prev = _head._prev;
        Link* head = &_head;

        // Link* rnext = rhs._head._next;
        // Link* rprev = rhs._head._prev;
        // Link* rhead = &rhs._head;

        // _head._next->_prev = rhead;
        _head._next->_prev = &rhs._head;
        // _head._next        = rnext;
        _head._next        = rhs._head._next;

        rhs._head._next->_prev = head;
        rhs._head._next        = next;
        
        // _head._prev->_next = rhead;
        // _head._prev        = rprev;
        _head._prev->_next = &rhs._head;
        _head._prev        = rhs._head._prev;

        rhs._head._prev->_next = head;
        rhs._head._prev        = prev;
    }

    void splice(const_iterator pos, List& other, const_iterator first, const_iterator last)
    {
        if (first == last) return;
        --last;

        Link* tmp = first._ptr->_prev;

        first._ptr->_prev->_next = last._ptr->_next;
        first._ptr->_prev = pos._ptr->_prev;

        pos._ptr->_prev->_next = first._ptr;

        last._ptr->_next->_prev = tmp;
        last._ptr->_next = pos._ptr;

        pos._ptr->_prev = last._ptr;
    }

    bool Invariant() const
    {
        size_t length = 0;
        for (const_iterator it = cbegin(); it != cend(); ++it)
        {
            if (it._ptr->_next == nullptr) return false;
            if (it._ptr->_prev == nullptr) return false;

            length++;
        }

        return length == Count() 
            && length == size()
            && _head._next != nullptr
            && _head._prev != nullptr;
    }

    iterator insert(iterator pos, const T& value)
    {
        pos._ptr->insert_before(new Node(value));
        return pos._ptr->_prev;
    }

    iterator erase(const iterator& pos)
    {
        delete (pos._ptr->_prev->delete_after());
        return pos._ptr->_next;
    }

    std::ostream& Print(std::ostream& cout) const
    {
        for (auto it = cbegin(); it != cend(); ++it)
            cout << *it << " ";
        return cout;
    }

    friend bool operator ==(const List& lhs, const List& rhs)
    {
        const_iterator lIt = lhs.begin();
        const_iterator rIt = rhs.begin();
        for (; lIt != lhs.end() && rIt != rhs.end(); ++lIt, ++rIt)
            if (*lIt != *rIt)
                return false;
        return (lIt == lhs.end()) && (rIt == rhs.end());
    }

    friend bool operator <(const List& lhs, const List& rhs)
    {
        const_iterator lIt = lhs.begin();
        const_iterator rIt = rhs.begin();
        for (; lIt != lhs.end() && rIt != rhs.end(); ++lIt, ++rIt)
            if (*lIt < *rIt)
                return true;
            else if (*lIt > *rIt)
                return false;
        return (rIt != rhs.end());
    }

    friend bool operator !=(const List& l, const List& r) { return !(l == r); }
    friend bool operator > (const List& l, const List& r) { return  (r  < l); }
    friend bool operator <=(const List& l, const List& r) { return !(r  < l); }
    friend bool operator >=(const List& l, const List& r) { return !(l  < r); }
    
    template <typename U>
    friend std::ostream& operator<<(std::ostream& cout, const List<U>& other)
    {
        return other.Print(cout);
    }

    friend void swap(List<T>& lhs, List<T>& rhs) { lhs.swap(rhs); }
};

#endif
