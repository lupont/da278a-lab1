#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cassert>
#include <iterator>
#include <stdlib.h>

template<class T>
class List {
    /* Forward Declarations */
    template<class U> class ListIter;
    #define CHECK assert(Invariant());

    class Node;

public:
    using iterator = ListIter<T>;
    using const_iterator = ListIter<const T>;

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
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using reference = X&;
        using pointer = X*;

        friend class List;
        Node* _ptr;

    public:
        ListIter(const Link* p) : _ptr(static_cast<Node*>(const_cast<Link*>(p))) {}
        ListIter() = default;
        ListIter(const ListIter& other)
        {
            _ptr = other._ptr;
        }

        ~ListIter() = default;

        ListIter& operator=(const ListIter& other)
        {
            if (&other == this)
                return *this;

            _ptr = other._ptr;
            return *this;
        }

        X& operator*() { return _ptr->_data; }

        X* operator->() { return &_ptr->_data; }

        ListIter& operator++()
        {
            _ptr = static_cast<Node*>(_ptr->_next);
            return *this;
        }

        ListIter operator++(int)
        {
            auto tmp(*this);
            operator++();
            return tmp;
        }

        ListIter& operator--()
        {
            _ptr = static_cast<Node*>(_ptr->_prev);
            return *this;
        }

        ListIter operator--(int)
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

        while (*ptr != '\0') ++ptr;
        --ptr;

        while (ptr >= str)
            push_front(*ptr--);

        CHECK
    }

    ~List()
    {
        while (_head._next != &_head)
            pop_front();
        CHECK
    }

    List& operator=(const List& other);

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

    size_t size() const noexcept { return Count(); }

    size_t Count() const noexcept
    {
        size_t length = 0;
        for (const_iterator it = cbegin(); it != cend(); ++it)
            length++;
        return length;
    }

    void push_back(const T& value)
    {
        _head.insert_before(new Node(value));
        CHECK
    }

    void push_front(const T& value)
    {
        _head.insert_after(new Node(value));
        CHECK
    }

    void pop_back()
    {
        // delete (_head._prev->delete_after());
        delete (_head.delete_before());
        CHECK
    }

    void pop_front()
    {
        delete (_head.delete_after());
        CHECK
    }

    void swap(List<T>& rhs);                     // TODO: move to Link?
    void splice(const_iterator pos, List& other, // TODO: move to Link? rename List to list?
                const_iterator first,
                const_iterator last);

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

    friend bool operator !=(const List& lhs, const List& rhs) { return !(lhs == rhs); }
    friend bool operator > (const List& lhs, const List& rhs) { return  (rhs <  lhs); }
    friend bool operator <=(const List& lhs, const List& rhs) { return !(rhs <  lhs); }
    friend bool operator >=(const List& lhs, const List& rhs) { return !(lhs <  rhs); }
    
    template <typename U>
    friend std::ostream& operator<<(std::ostream& cout, const List<U>& other)
    {
        return other.Print(cout);
    }

    bool Invariant() const { return true; }

    friend void swap(List<T>& lhs, List<T>& rhs) // O(1)
    {
        Link tmp = lhs._head;
        lhs._head = rhs._head;
        rhs._head = tmp;
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
        for (const_iterator it = cbegin(); it != cend(); ++it)
        {
            cout << *it << " ";
        }

        cout << "(size: " << Count() << ")";

        cout << std::endl;
        return cout;
    }
};

#endif
