/**
 * @file: task/list_impl.h
 * Solution implementation of the programming task 1
 */

namespace Task
{
// ---- DList::Unit class implementation ----

    template <class T>
    DList<T>::Unit::Unit():             //<standart constructor
        next_u(NULL) , prev_u(NULL){}

    template <class T>
    DList<T>::Unit::Unit(const T& val):             //<constructor with parameter (T& val)
        next_u(NULL) , prev_u(NULL) , data(val){}

    template <class T>
    DList<T>::Unit::~Unit(){}       //<destructor

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


    template <class T> DList<T>::DList():           //<constructor
        first_u(NULL) , last_u(NULL) , count(0){}

    template <class T> DList<T>::~DList()           //<destructor
    {
        clear();
    }

    template <class T> void DList<T>::push_front (const T& val)
    {
        Unit* U;

        //memory allocation
        try
        {
            U = new Unit (val);
        }
        catch (std::bad_alloc& ba)
        {
            std::cerr << "bad_alloc caught: " << ba.what() << endl;
        }

        //special case of empty list
        if(count==0)
        {
            first_u=U;
            last_u=U;
            count++;
            return;
        }

        //count!=0, List is not empty
        first_u->set_prev(U);
        U->set_next(first_u);
        first_u=U;
        count++;
    }

    template <class T> void DList<T>::pop_front()
    {
        //Error case
        if(count==0)
            throw Error("Error: invalid application of POP() function, list is empty");

        if(count==1)
        {
            delete first_u;
            first_u=NULL;
            last_u=NULL;
            count=0;
            return;
        }

        first_u=first_u->next();
        delete first_u->prev();
        first_u->set_prev(NULL);
        count--;
    }

    template <class T> void DList<T>::push_back (const T& val)
    {
        Unit* U;

        //memory allocation
        try
        {
            U = new Unit (val);
        }
        catch (std::bad_alloc& ba)
        {
            std::cerr << "bad_alloc caught: " << ba.what() << endl;
        }

        //special case of empty list
        if(count==0)
        {
            first_u=U;
            last_u=U;
            count++;
            return;
        }

        //count!=0, List is not empty
        last_u->set_next(U);
        U->set_prev(last_u);
        last_u=U;
        count++;
    }

    template <class T> void DList<T>::pop_back()
    {
        //Error case
        if(count==0)
            throw Error("Error: invalid application of POP() function, list is empty");

        if(count==1)
        {
            delete last_u;
            first_u=NULL;
            last_u=NULL;
            count=0;
            return;
        }

        last_u=last_u->prev();
        delete last_u->next();
        last_u->set_next(NULL);
        count--;
    }

    template <class T> typename DList<T>::Unit *
    DList<T>::insert (typename DList<T>::Unit *u, const T& val)
    {
        //Note:
        //there must be test for bellonging of unit to the list
        //BUT requirements for time complexity does not allow us to do this
        //SO it's user responsibility

        Unit* TBe_inserted;

        //memory allocation
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
            count++;
        }
        else                        // u is not the first in the List
        {
            (u->prev())->set_next(TBe_inserted);
            u->set_prev(TBe_inserted);
            count++;
        }

        return TBe_inserted;
    }

    template <class T> typename DList<T>::Unit *
    DList<T>::first()
    {
        return first_u;//will return NULL  if List is empty
    }

    template <class T> typename DList<T>::Unit *
    DList<T>::last()
    {
        return last_u;//will return NULL  if List is empty
    }

    template <class T> typename DList<T>::Unit *
    DList<T>::erase (typename DList<T>::Unit *u)
    {
        //Note:
        //there must be test for bellonging of unit to the list
        //BUT requirements for time complexity does not allow us to do this
        //SO it's user responsibility

        if(u==NULL)
            throw Error("Error: invalid argument of ERASE() function, null pointer");

        if(count==0)
            return NULL;

        if(first_u==u && last_u==u) //<it's more safety than if(count==1)
        {
            first_u=NULL;
            last_u=NULL;
            count--;
            delete u;
            return NULL;
        }

        if(first_u==u && count>1) //u is the first and not only element of the list
        {
            first_u=first_u->next();
            first_u->set_prev(NULL);
            count--;
            delete u;
            return first_u;
        }

        if(last_u==u && count>1)//u is the last and not only element of the list
        {
            last_u=last_u->prev();
            last_u->set_next(NULL);
            count--;
            delete u;
            return NULL;
        }

        Unit *returned_val=u->next();
        (u->prev())->set_next(u->next());
        (u->next())->set_prev(u->prev());
        count--;
        delete u;

        return returned_val;
    }

    template <class T> void
    DList<T>::clear()
    {
        if(count==0)
            return;

        if(count==1)
        {
            delete first_u;
            first_u=NULL;
            last_u=NULL;
            count=0;
            return;
        }

        Unit* tmp=first_u;

        do{
            tmp=tmp->next();
            delete tmp->prev();
        }while(tmp!=last_u);

        delete last_u;

        first_u=NULL;
        last_u=NULL;
        count=0;
    }

    template <class T> bool
    DList<T>::empty()
    {
        return (count==0)?true:false;
    }

    template <class T> unsigned
    DList<T>::size()
    {
        return count;
    }

    template <class T> void
    DList<T>::reverse()
    {
        if(count==0 || count==1)
            return;

        Unit* to_be_set_the_last=first_u;
        Unit* tmp=first_u;

        //iterration for the first unit
        tmp=tmp->next();
        (tmp->prev())->set_next(NULL);
        (tmp->prev())->set_prev(tmp);
        //special case
        if(tmp==last_u)
        {
            last_u->set_next(first_u);
            last_u->set_prev(NULL);
            last_u=first_u;
            first_u=tmp;
            return;
        }


        do{
            tmp=tmp->next();
            (tmp->prev())->set_next((tmp->prev())->prev());
            (tmp->prev())->set_prev(tmp);
        }while(tmp!=last_u);
        //iterration for the last unit
        last_u->set_next(last_u->prev());
        last_u->set_prev(NULL);
        first_u=tmp;
        last_u=to_be_set_the_last;
    }

    template <class T> void
    DList<T>::dump()
    {


        using namespace std;
        Unit* tmp=first_u;

        cout<<"\n================================================="<<endl;
        cout<<"              Here's your List                   "<<endl;
        if(count==0)
        {
            cout<<"Your List is empty"<<endl;
            cout<<"================================================="<<endl;
            return;
        }
        cout<<"Size of your List is "<<size()<<"\n"<<endl;
        while(tmp!=last_u)
        {
                cout<<tmp->val()<<endl;
                cout<<" | "<<endl;
                cout<<" | "<<endl;
                tmp=tmp->next();
        }
        cout<<tmp->val()<<endl;
        cout<<"================================================="<<endl;

    }
// ---- End of DList template class implementation ----
};
