#ifndef LIST_H
#define LIST_H



#include <stdio.h>
#include <stdlib.h>
#include <exception.h>


//==============================================================================


template <class T>
class DList
{
public:

                Dlist       ();
               ~Dlist       ();

    void        push_front  (const t& val);
    void        pop_front   ();
    void        push_back   (const T& val);
    void        pop_back    ();
    Unit*       insert      (Unit* u, const T& val);
    Unit*       first       ();
    Unit*       last        ();
    Unit*       erase       (Unit* u);
    void        clear       ();
    bool        empty       ();
    unsigned    size        ();
    void        reverse     ();
    bool        ok          ();

    void        print       (FILE* stream);
    void        print       ();

    class       Unit;
protected:
    struct      BeginUnit;
    struct      EndUnit;
private:
    unsigned    __size;
    Unit*       __lborder;
    Unit*       __rborder;
};

//==============================================================================

template <class T>
class DList<T>::Unit
{
public:
                Unit        (T& copied);

    Unit*       next        ();
    Unit*       prev        ();
    T&          val         ();
    bool        ok          ();

    void        print(FILE* stream);
    void        print();
private:
                Unit        ();
    T*          __val;
    bool        __empty;
    Unit*       __next;
    Unit*       __prev;

};

//==============================================================================

#define __UNIT_TEMPLATE(name, ptr_name)             \
template <class T>                                  \
class DList<T>::#nameUnit: private DList<T>::Unit   \
{                                                   \
                                                    \
                     #nameUnit();                   \
                    ~#nameUnit();                   \
    const void*      ptr_name;                      \
};                                                  \

__UNIT_TEMPLATE(Begin, begin)
__UNIT_TEMPLATE(End, end)

#undef __UNIT_TEMPLATE

#endif // LIST_H
