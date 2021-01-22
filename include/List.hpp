#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cassert>
#include <iterator>
#include <stdlib.h>

template<class T>
class List {
    template<class U> class ListIter;
    #define CHECK assert(Invariant());

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
        iterator insert(iterator pos, const T& value) // TODO: move to Link?
        {

        }

        iterator erase(const iterator& pos)           // TODO: move to Link?
        {

        }

        // insert, erase, splice, osv
    };

    class Node : public Link {
        friend class List;
        T _data;

    public:
        Node(const T& data) : _data(data) {}
    };

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
        ListIter(List<T>::Link* p) : _ptr(static_cast<Node*>(const_cast<Link*>(p))) {}
        ListIter() = default;
        ListIter(const ListIter&) = default;

        ~ListIter() = default;

        ListIter& operator=(const ListIter& other)
        {
            _ptr = other._ptr;
        }

        X& operator*() { return _ptr->_data; }

        X* operator->() { return &_ptr->_data; }

        ListIter& operator++() // ska inte kontrollera om man är utanför listan, utan lämna det problemet åt programmeraren
        {
            _ptr = static_cast<Node*>(_ptr->_next);
            return *this;
        }

        ListIter operator++(int)
        {
            auto temp(*this);
            operator++();
            return temp;
        }

        ListIter& operator--() {}

        ListIter operator--(int foo) {}

        friend bool operator ==(const ListIter& lhs, const ListIter& rhs)
        {
            return lhs._ptr == rhs._ptr;
        }

        friend bool operator !=(const ListIter& lhs, const ListIter& rhs)
        {
            return !(lhs == rhs);
        }
    };

    Link _head;

public:
    List() = default;
    List(const List& other);
    List(const char* str) : List()
    {
        const char* ptr = str;
        while (*ptr != '\0')
            ++ptr;
        for (; ptr >= str; --ptr)
            push_front(*ptr);
        CHECK
    }

    ~List() = default;

    List& operator=(const List& other);

          T& front()       { return static_cast<Node*>(_head._next)->_data; }
    const T& front() const { return static_cast<Node*>(_head._next)->_data; }

          T& back()        { return static_cast<Node*>(_head._prev)->_data; }
    const T& back()  const { return static_cast<Node*>(_head._prev)->_data; }

    iterator       begin()        noexcept { return iterator(_head._next);       }
    iterator       end()          noexcept { return iterator(_head._prev);       }
    const_iterator begin()  const noexcept { return const_iterator(_head._next); }
    const_iterator end()    const noexcept { return const_iterator(_head._prev); }
    const_iterator cbegin() const noexcept { return const_iterator(_head._next); }
    const_iterator cend()   const noexcept { return const_iterator(_head._prev); }

    bool empty() const noexcept
    {
        return begin() == end();
    }

    size_t size() const noexcept
    {
        return Count();
    }

    size_t Count() const noexcept
    {
        const Link* l = &_head;
        size_t length = 0;
        size_t attempts = 0;

        while (true)
        {
            l = l->_next;
            if (l->_prev == l->_next)
                break;
            else if (attempts > 1000)
            {
                std::cout << "too many attempts" << std::endl;
                break;
            }

            length++;
            attempts++;
        }
        return length;
    }

    void push_back(const T& value)
    {
        Node* node = new Node { value };
        node->_next = &_head;
        node->_prev = _head._prev;

        _head._prev->_next = node;
        _head._prev = node;
    }

    void push_front(const T& value)
    {
        Node* node = new Node { value };
        node->_next = _head._next;
        node->_prev = &_head;

        _head._next = node;
    }

    void pop_back()
    {
        Link* n1 = _head._prev;
        _head._prev = n1;
        delete n1;
    }

    void pop_front()
    {
        _head._next = _head._next->_next;
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
        auto lIt = lhs.begin();
        auto rIt = rhs.begin();
        for (; lIt != lhs.end() && rIt != rhs.end(); ++lIt, ++rIt)
            if (*lIt < *rIt)
                return true;
            else if (*lIt > *rIt)
                return false;
        return (rIt != rhs.end());
    }

    friend bool operator !=(const List& lhs, const List& rhs) { return !(lhs == rhs); }
    friend bool operator > (const List& lhs, const List& rhs) { return rhs < lhs;     }
    friend bool operator <=(const List& lhs, const List& rhs) { return !(rhs < lhs);  }
    friend bool operator >=(const List& lhs, const List& rhs) { return !(lhs < rhs);  }
    
    template <typename U>
    friend std::ostream& operator<<(std::ostream& cout, const List<U>& other)
    {
        return cout;
    }

    bool Invariant() const
    {
        size_t i = 0;
        for (auto p = &_head; p->_prev != p->_next; p = p->_next)
            if (++i == std::numeric_limits<size_t>::max())
                return false;
        return true;
    }

    friend void swap(List<T>& lhs, List<T>& rhs); // O(1)

    iterator insert(iterator pos, const T& value); // TODO: move to Link?
    iterator erase(const iterator& pos);           // TODO: move to Link?

    void Print(std::ostream& cout)
    {
        cout << "printing" << std::endl;
    }
};


#endif
