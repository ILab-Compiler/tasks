/**
 * @file: task/list_impl.h
 * Solution implementation of the programming task 1
 */

namespace Task
{
// ---- DList::Unit class implementation ----

    template <class T>
    DList<T>::Unit::Unit:
        next(NULL) , prev(NULL){}

    template <class T>
    DList<T>::Unit::Unit(const T& val)
        next(NULL) , prev(NULL) , data(val){}


    template <class T> typename DList<T>::Unit *
    DList<T>::Unit::next()
    {
        return DList<T>::Unit::next;
    }

    template <class T> void
    DList<T>::Unit::set_next(Unit *u)


    template <class T> typename DList<T>::Unit *
    DList<T>::Unit::prev()
    {
        return DList<T>::Unit::prev;
    }

    template <class T> typename DList<T>::T&
    DList<T>::Unit::val()
    {
        return DList<T>::Unit::val;
    }

// ---- End of DList::Unit class implementation ----

// ---- DList template class implementation ----


    template <class T> void DList<T>::DList():
        first(NULL) , last(NULL){}

    template <class T> void DList<T>::push_front (const T& val)
    {
        Unit U(const T& val);

    }

// ---- End of DList template class implementation ----
};
