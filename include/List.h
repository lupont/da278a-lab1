#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <stdlib.h>

template<class T>
class List {
    class Node;

    class Link {
        friend class List<T>;
        Link* _next;
        Link* _prev;

        Link() : _next(this), _prev(this) {}

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
        /* typedef ... iterator_category; */
        /* typedef ... value_type; */
        /* typedef ... difference_type; */
        /* typedef ... reference; */
        /* typedef ... pointer; */
        friend class List;
        Link* _ptr;

    public:
        /* ListIter(Node<T>* p); */
        ListIter();
        ListIter(const ListIter& other);

        ListIter& operator=(const ListIter& other);

        T& operator*();
        T* operator->();

        ListIter& operator++();
        ListIter& operator--();
        ListIter operator++(int);
        ListIter operator--(int);

        friend bool operator ==(const ListIter& lns,
                                const ListIter& rhs);
        friend bool operator !=(const ListIter& lhs,
                                const ListIter& rhs);
    };

    using iterator = ListIter<T>;
    using const_iterator = const ListIter<T>; // TODO: check this

    Link _head;

public:
    List();
    List(const List& other);
    List(const char* other);

    ~List();

    List& operator=(const List& other);

    T& front();
    const T& front() const;

    T& back();
    const T& back() const;

    iterator begin() noexcept;
    iterator end()   noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;

    iterator insert(iterator pos, const T& value); // TODO: move to Link?
    iterator erase(const iterator& pos);           // TODO: move to Link?

    void push_back(const T& value);
    void push_front(const T& value);

    void pop_back();
    void pop_front();

    void swap(List<T>& rhs);                     // TODO: move to Link?
    void splice(const_iterator pos, List& other, // TODO: move to Link? rename List to list?
                const_iterator first,
                const_iterator last);

    friend bool operator ==(const List& lns, const List& rhs);
    friend bool operator <(const List& lhs, const List& rhs);

    friend bool operator !=(const List& lns, const List& rhs);
    friend bool operator >(const List& lns, const List& rhs);
    friend bool operator <=(const List& lns, const List& rhs);
    friend bool operator >=(const List& lns, const List& rhs);
    
    friend std::ostream& operator<<(std::ostream& cout, const List& other);

    #define CHECK assert(Invariant());
    bool Invariant();

    friend void swap(List<T>& lhs, List<T>& rhs); // O(1)
};


#endif
