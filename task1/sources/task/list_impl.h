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
    DList<T>::Unit::set_next(typename DList<T>::Unit *u)
    {
        next_u=u;
    }

    template <class T> typename DList<T>::Unit *
    DList<T>::Unit::prev()
    {
        return prev_u;
    }

    template <class T> void
    DList<T>::Unit::set_prev(typename DList<T>::Unit *u)
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
        first_u(NULL) , last_u(NULL) , count(0){}

    template <class T> void DList<T>::push_front (const T& val)
    {
        Unit* U;

        try
        {
            U = new Unit (val);
        }
        catch (std::bad_alloc& ba)
        {
            std::cerr << "bad_alloc caught: " << ba.what() << endl;
        }

        if(count==0)
        {
            first_u=U;
            last_u=U;
            count++;
        }

        //count!=0, List is not empty
        first_u->set_prev(U);
        U->set_next(first_u);
        first_u=U;
        count++;
    }

    template <class T> void DList<T>::pop_front()
    {
        if(count==0)
        {
            std::cout<<"Error: invalid application POP() function, list is empty"<<endl;
            abort();
        }
        first_u=first_u->next();
        delete first_u->prev();
        first_u->set_prev(NULL);
        count--;
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
            std::cerr << "bad_alloc caught: " << ba.what() << endl;
        }

        if(count==0)
        {
            first_u=U;
            last_u=U;
            count++;
        }

        //count!=0, List is not empty
        last_u->set_next(U);
        U->set_prev(last_u);
        last_u=U;
        count++;
    }

    template <class T> void DList<T>::pop_back()
    {
        if(count==0)
        {
            std::cout<<"Error: invalid application POP() function, list is empty"<<endl;
            abort();
        }
        last_u=last_u->prev();
        delete last_u->next();
        last_u->set_next(NULL);
        count--;
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
            std::cerr << "bad_alloc caught: " << ba.what() << endl;
        }

        TBe_inserted->set_prev(u->prev());
        TBe_inserted->set_next(u);

        if( u->prev() == NULL)      // u is the first in the List
        {
            first_u=TBe_inserted;
            u->set_prev(TBe_inserted);
        }
        else                        // u is not the first in the List
        {
        (u->prev())->set_next(TBe_inserted);
        u->set_prev(TBe_inserted);
        }

        return TBe_inserted;
    }

    template <class T> typename DList<T>::Unit *
    DList<T>::first()
    {
        return first_u;//will return Null  if List is empty!!!!
    }

    template <class T> typename DList<T>::Unit *
    DList<T>::last()
    {
        return last_u;//will return Null  if List is empty!!!!
    }

    template <class T> typename DList<T>::Unit *
    DList<T>::erase (typename DList<T>::Unit *u)
    {
        //throw if u==Null проверка принадлежности к

        if(first_u==u && last_u==u)
        {
            first_u=NULL;
            last_u=NULL;
            count--;
            delete u;
            return NULL;
        }

        if(first_u==u && count>1)
        {
            first_u=first_u->next();
            count--;
            delete u;
            return first_u;
        }

        if(last_u==u && count>1)
        {
            last_u=last_u->prev();
            count--;
            delete u;
            return NULL;
        }

        (u->prev())->set_next(u->next());
        (u->next())->set_prev(u->prev());
        count--;
        u=u->next();
        delete u->prev();

        return u;
    }

    template <class T> void
    DList<T>::clear()
    {
        if(count==0)
            return;

        Unit* tmp=first_u;

        do{
            tmp=tmp->next();
            delete tmp->prev();
        }while(tmp!=last_u);

        first_u=NULL;
        last_u=NULL;
        count=0;
    }
// ---- End of DList template class implementation ----
};
