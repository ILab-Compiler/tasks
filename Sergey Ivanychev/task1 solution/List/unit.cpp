#include <list.h>


/*
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
*/

#define __CONSTR_TEMP(name)     \
template <class T>              \
DList<T>::#nameUnit():          \
ptr_name((void*)this)           \
{}                              \

#define __DESTR_TEMP(name)      \
template <class T>              \
DList<T>::~#nameUnit():         \
ptr_name((void*)POISON)         \
{}                              \

__CONSTR_TEMP(Begin)
__DESTR_TEMP(Begin)
__CONSTR_TEMP(End)
__DESTR_TEMP(End)

#undef __CONSTR_TEMP
#undef __DESTR_TEMP

//==============================================================================

template <class T>
DList<T>::Unit():
    __val (NULL),
    __empty(true),
    __next(NULL),
    __prev(NULL)
{}

template <class T>
DList<T>::Unit(T& copied):
    DList<T>::Unit()
{
    this->__val = new T;
    *(__val) = copied;

    __empty = false;
}

//==============================================================================

template <class T>
DList<T>::~Unit():
{
    if (__val != NULL)
    {
        delete __val;
        __val = NULL;
    }
    __next = NULL;
    __prev = NULL;
    __empty = true;
}

//==============================================================================

template <class T>
Unit* DList<T>::Unit::next()
{
    RT_ASSERT(this->__next != NULL, "NEXT pointer in UNIT object is NULL");
    if (this->__next == __rborder)
        return NULL;
    return this->__next;
}

//==============================================================================

template <class T>
Unit* DList<T>::Unit::prev()
{
    RT_ASSERT(this->__preb != NULL, "NEXT pointer in UNIT object is NULL");
    if (this->__prev == __lborder)
        return NULL;
    return this->__prev;
}

//==============================================================================

template <class T>
T& DList<T>::Unit::val()
{
    RT_ASSERT(this->__val != NULL, "VAL pointer in NEXT object is NULL");
    T& ret = *(__val);

    return ret;
}

//==============================================================================

template <class T>
bool DList<T>::Unit::ok()
{
    if (__empty == false && __val == NULL)  return false;
    if (__empty == true  && __val != NULL)  return false;
    if (__next  == NULL)                    return false;
    if (__prev  == NULL)                    return false;

    return true;
}

