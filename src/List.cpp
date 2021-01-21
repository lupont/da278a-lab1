#include "../include/List.h"

template <class T>
List<T>::List(const List& other)
{
    _head = Link();
}

template <class T>
List<T>::List(const char* other)
{
    _head = Link();
}

template <class T>
List<T>& List<T>::operator=(const List& other)
{

}

/* template <class T> */
/* T& List<T>::front() */
/* { */
/*     return _head._next; */
/* } */

/* template <class T> */
/* const T& List<T>::front() const */
/* { */
/*     return _head._next; */
/* } */

/* template <class T> */
/* T& List<T>::back() */
/* { */
/*     return _head._prev; */
/* } */

/* template <class T> */
/* const T& List<T>::back() const */
/* { */
/*     return _head._prev; */
/* } */

template <class T>
typename List<T>::iterator List<T>::begin() noexcept
{

}

template <class T>
typename List<T>::iterator List<T>::end() noexcept
{

}

/* template <class T> */
/* bool List<T>::empty() const noexcept */
/* { */
/*     return false; */
/*     /1* return _head._next != nullptr; *1/ */
/* } */

template <class T>
size_t List<T>::size() const noexcept
{

}

template <class T>
typename List<T>::iterator List<T>::insert(iterator pos, const T& value) // TODO: move to Link?
{

}

template <class T>
typename List<T>::iterator List<T>::erase(const iterator& pos)           // TODO: move to Link?
{

}

/*template <class T>*/
/*void List<T>::push_back(const T& value)*/
/*{*/
/*    */
/*       [H] -> [N1] -> [N2]*/
/*       h.next = N1*/
/*       h.prev = N2*/

/*       N1.next = N2*/
/*       N1.prev = H*/

/*       N2.next = H*/
/*       N2.prev = N1*/

/*       push_back([N3])*/

/*       [H] -> [N1] -> [N2] -> [N3]*/

/*       h.next = N1*/
/*       h.prev = N3 **/

/*       N1.next = N2*/
/*       N1.prev = H*/

/*       N2.next = N3 **/
/*       N2.prev = N1*/

/*       N3.next = H*/
/*       N3.prev = N2*/

/*   */

/*    Node node = new Node { value };*/
/*    node._next = _head;*/
/*    node._prev = _head._prev;*/

/*    _head._prev._next = node;*/
/*    _head._prev = node;*/

/*}*/

/*template <class T>*/
/*void List<T>::push_front(const T& value)*/
/*{*/
/*    */
/*       [H] -> [N1] -> [N2]*/
/*       h.next = N1*/
/*       h.prev = N2*/

/*       N1.next = N2*/
/*       N1.prev = H*/

/*       push_front([N3])*/

/*       [H] -> [N3] -> [N1] -> [N2]*/
/*       h.next = N3 **/
/*       h.prev = N2*/

/*       N3.next = N1*/
/*       N3.prev = H*/

/*       N1.next = N2*/
/*       N1.prev = N3 **/

/*    */
/*    Node node = new Node { value };*/
/*    node._next = _head._next;*/
/*    node._prev = _head;*/

/*    _head._next = node;*/
/*}*/

template <class T>
void List<T>::pop_back()
{
    _head._prev = _head._prev._prev;
}

template <class T>
void List<T>::pop_front()
{
    _head._next = _head._next._next;
}

template <class T>
void List<T>::swap(List<T>& rhs) // TODO: move to Link?
{

}

template <class T>
void List<T>::splice(const_iterator pos, List& other, // TODO: move to Link? rename List to list?
            const_iterator first,
            const_iterator last)
{

}

#define CHECK assert(Invariant());
template <class T>
bool List<T>::Invariant()
{

}

template <class T>
const bool List<T>::Invariant() const
{

}

template <class T>
void swap(List<T>& lhs, List<T>& rhs) // O(1)
{

}

/* template <class T> */
/* std::ostream& operator<<(std::ostream& cout, const List<T>& other) */
/* { */

/* } */

/* ListIter(Node<T>* p); */
template <class T>
typename List<T>::iterator ListIter()
{

}

template <class T>
typename List<T>::iterator insert(typename List<T>::iterator pos, const T& value) // TODO: move to Link?
{

}

template <class T>
typename List<T>::iterator erase(const typename List<T>::iterator& pos)           // TODO: move to Link?
{

}

