/**
 * @file: 	task/unit_impl.h 
 * @brief	The header with implementation of Unit template methods
 * 
 * @author	Sergey Ivanychev, DCAM MIPT
 */

#include "exception.h"
#include "stdio.h"
//=============================================================================================

namespace Task
{

/**
 * @brief 	Standard Unit constructors and destructor.
 * @details 	There are two constructors of list. Note that Unit() is private method and it is
 * 		prohibited to use it	 
 */
template <class T>
DList<T>::Unit::Unit():
__empty(true),
__val(NULL),
__prev(NULL),
__next(NULL)
{}

template<class T>
DList<T>::Unit::Unit(const T& val):
Unit()
{
	CALL(__val = new T(val), "Copying failed");
	RT_ASSERT(__val != NULL, ARG_OBJ_COPY_FAIL);
	__empty = false;
}

template <class T>
DList<T>::Unit::~Unit()
{
	if (__val != NULL)
	{
		delete __val;
		__val = NULL;
	}

	__empty = true;
	__next = NULL;
	__prev = NULL;
}
//=============================================================================================

/**
 * @brief Next() and prev()
 * @details Return the pointer to the next unit in list or to the previous one
 * 
 * @return Wanted pointer
 */
template <class T>
typename DList<T>::Unit*
DList<T>::Unit::next()
{
	return __next;
}

template <class T>
typename DList<T>::Unit*
DList<T>::Unit::prev()
{
	return __prev;
}
//=============================================================================================

/**
 * @brief Val()
 * @return Value of unit
 */

template <class T>
T&
DList<T>::Unit::val()
{
	RT_ASSERT(__val != NULL, NO_VALUE_IN_OBJ);
	return *(__val);
}
//=============================================================================================

/**
 * @brief Dump()
 * @details Provides detailed print about argumented unit
 * 
 * @param stream File stream to write in
 */

template <class T>
void
DList<T>::Unit::dump(FILE* stream)
{
	assert(stream);
	fprintf(stream, "Unit [%08x]\n"
					"Status %s\n"
					"__empty = %s\n"
					"__val  = [%08x]\n"
					"__prev = [%08x]\n"
					"__next = [%08x]\n",
					this,
					(ok())? "OK" : "BAD",
					(__empty)? "TRUE": "FALSE",
					__val,
					__prev,
					__next);
}

template <class T>
void
DList<T>::Unit::dump()
{
	this -> dump(stdout);
}
//=============================================================================================

/**
 * @brief Ok()
 * @details Unit condition verificator
 * 
 * @return True, if the unit is OK.
 */
template <class T>
bool
DList<T>::Unit::ok()
{
	if (__empty  &&  __val)
		return false;
	if (!__empty && !__val)
		return false;
	return true;
}


};
