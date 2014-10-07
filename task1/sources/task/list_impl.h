/**
 * @file: task/list_impl.h
 * Solution implementation of the programming task 1
 */

namespace Task
{
// ---- DList::Unit class implementation ----

    template <class T>
    DList<T>::Unit::Unit():
        next_u(NULL) , prev_u(NULL){}

    template <class T>
    DList<T>::Unit::Unit(const T& val):
        next_u(NULL) , prev_u(NULL) , data(val){}


    template <class T> typename DList<T>::Unit *
    DList<T>::Unit::next()
    {
        return next_u;
    }

    template <class T> void
    DList<T>::Unit::set_next(Unit *u)
    {
        next_u=u;
    }

    template <class T> typename DList<T>::Unit *
    DList<T>::Unit::prev()
    {
        return prev_u;
    }

    template <class T> void
    DList<T>::Unit::set_prev(Unit *u)
    {
        prev_u=u;
    }

    template <class T> T&
    DList<T>::Unit::val()
    {
        return data;
    }

// ---- End of DList::Unit class implementation ----

// ---- DList template class implementation ----


    template <class T> DList<T>::DList():
        first_u(NULL) , last_u(NULL){}

    template <class T> void DList<T>::push_front (const T& val)
    {
        Unit* U;

        try
        {
            U = new Unit (val);
        }
        catch (std::bad_alloc& ba)
        {
            std::cerr << "bad_alloc caught: " << ba.what() << '\n';
        }

        first_u->set_prev(U);
        U->set_next(first_u);
        first_u=U;
    }

    template <class T> void DList<T>::pop_front()
    {
        first_u=first_u->next();
        delete first_u->prev();
        first_u->set_prev(NULL);
    }

    template <class T> void DList<T>::push_back (const T& val)
    {
        Unit* U;

        try
        {
            U = new Unit (val);
        }
        catch (std::bad_alloc& ba)
        {
            std::cerr << "bad_alloc caught: " << ba.what() << '\n';
        }

        last_u->set_next(U);
        U->set_prev(last_u);
        last_u=U;
    }

    template <class T> void DList<T>::pop_back()
    {
        last_u=last_u->prev();
        delete last_u->next();
        last_u->set_next(NULL);
    }

    template <class T> typename DList<T>::Unit *
    DList<T>::insert (typename DList<T>::Unit *u, const T& val)
    {
        //throw here Unit!=NULL; does Unit belong the List?
        Unit* TBe_inserted;

        try
        {
            TBe_inserted = new Unit (val);
        }
        catch (std::bad_alloc& ba)
        {
            std::cerr << "bad_alloc caught: " << ba.what() << '\n';
        }

        TBe_inserted->set_prev(u->prev());
        TBe_inserted->set_next(u);
        (u->prev())->set_next(TBe_inserted);
        u->set_prev(TBe_inserted);

        return TBe_inserted;
    }

    template <class T> typename DList<T>::Unit *
    DList<T>::first()
    {
        return first_u;
    }

    template <class T> typename DList<T>::Unit *
    DList<T>::last()
    {
        return last_u;
    }

// ---- End of DList template class implementation ----
};
