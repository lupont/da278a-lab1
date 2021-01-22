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

          T& front()       { return static_cast<Node*>(_head._next)->_data; }
    const T& front() const { return static_cast<Node*>(const_cast<Link*>(_head._next))->_data; }

          T& back()        { return static_cast<Node*>(_head._prev)->_data; }
    const T& back()  const { return static_cast<Node*>(const_cast<Link*>(_head._prev))->_data; }

    iterator begin() noexcept;
    iterator end()   noexcept;

    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    bool empty() const noexcept
    {
        return _head._next != nullptr;
    }

    size_t Count() const noexcept
    {
        return -1;
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
        // [H] -> [N1] -> [N2]
        // H.next = N1
        // H.prev = N2
        // 
        // N1.next = N2
        // N1.prev = H
        // 
        // N2.next = H
        // N2.prev = N1
        // 
        // pop_back()
        // 
        // [H] -> [N1]
        // H.next = N1
        // H.prev = N1 *
        // 
        // N1.next = H *
        // N1.prev = H
        // 
        // pop_back()
        // 
        // [H]
        // H.next = null *
        // H.prev = null *

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
    bool Invariant()
    {
        return true;
    }

    const bool Invariant() const
    {
        return true;
    }

    friend void swap(List<T>& lhs, List<T>& rhs); // O(1)

    iterator insert(iterator pos, const T& value); // TODO: move to Link?
    iterator erase(const iterator& pos);           // TODO: move to Link?
};


#endif