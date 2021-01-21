#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <stdlib.h>

template<class T>
class List {
    template<class U> class ListIter;

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
        iterator insert(iterator pos, const T& value); // TODO: move to Link?
        iterator erase(const iterator& pos);           // TODO: move to Link?

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
        Link* _ptr;

    public:
        ListIter(List<T>::Node* p);
        ListIter();
        ListIter(const ListIter&) = default;

        ~ListIter() = default;

        ListIter& operator=(const ListIter& other)
        {

        }

        T& operator*()
        {

        }

        T* operator->()
        {

        }

        ListIter& operator++() // ska inte kontrollera om man är utanför listan, utan lämna det problemet åt programmeraren
        {

        }

        ListIter& operator--()
        {
            
        }

        ListIter operator++(int foo)
        {

        }

        ListIter operator--(int foo)
        {

        }

        friend bool operator ==(const ListIter& lhs, const ListIter& rhs)
        {

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
    List(const char* other);

    ~List() = default;

    List& operator=(const List& other);

    T& front() { return _head._next; }
    const T& front() const { return _head._next; }

    T& back() { return _head._prev; }
    const T& back() const { return _head._prev; }

    iterator begin() noexcept;
    iterator end()   noexcept;

    bool empty() const noexcept { return false; }
    size_t size() const noexcept;

    void push_back(const T& value)
    {
        Node node = new Node { value };
        node._next = _head;
        node._prev = _head._prev;

        _head._prev._next = node;
        _head._prev = node;
    }

    void push_front(const T& value)
    {
        Node node = new Node { value };
        node._next = _head._next;
        node._prev = _head;

        _head._next = node;
    }

    void pop_back();
    void pop_front();

    void swap(List<T>& rhs);                     // TODO: move to Link?
    void splice(const_iterator pos, List& other, // TODO: move to Link? rename List to list?
                const_iterator first,
                const_iterator last);

    friend bool operator ==(const List& lns, const List& rhs)
    {

    }

    friend bool operator <(const List& lhs, const List& rhs)
    {

    }

    friend bool operator !=(const List& lhs, const List& rhs)
    { return !(lhs == rhs); }

    friend bool operator >(const List& lhs, const List& rhs)
    { return rhs < lhs; }

    friend bool operator <=(const List& lhs, const List& rhs)
    { return !(rhs < lhs); }

    friend bool operator >=(const List& lhs, const List& rhs)
    { return !(lhs < rhs); }
    
    template <typename U>
    friend std::ostream& operator<<(std::ostream& cout, const List<U>& other)
    {
        return cout;
    }

    #define CHECK assert(Invariant());
    bool Invariant();
    const bool Invariant() const;

    friend void swap(List<T>& lhs, List<T>& rhs); // O(1)

    iterator insert(iterator pos, const T& value); // TODO: move to Link?
    iterator erase(const iterator& pos);           // TODO: move to Link?
};


#endif
