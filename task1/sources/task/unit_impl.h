/**
 * @file: task/unit_impl.h 
 * Solution implementation of the programming task 1
 */

#include "exception.h"
#include "stdio.h"

namespace Task
{

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

	template <class T>
	typename DList<T>::Unit*
	DList<T>::Unit::next()
	{
		if (&__next != (DList<T>::Unit*)(&__rborder))
			return __next;
	}

	template <class T>
	typename DList<T>::Unit*
	DList<T>::Unit::prev()
	{
		if (&__prev != (DList<T>::Unit*)(&__lborder))
			return __prev;
	}

	template <class T>
	T&
	DList<T>::Unit::val()
	{
		RT_ASSERT(__val != NULL, NO_VALUE_IN_OBJ);
		return *(__val);
	}

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
						(__empty)? "TRUE": "FALSE",
						(ok())? "OK" : "BAD",
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

	template <class T>
	bool
	DList<T>::Unit::ok()
	{
		if (__empty  &&  __val)
			return false;
		if (!__empty && !__val)
			return false;
		if (!__prev || !__next)
			return false;
		return true;
	}


	template <class T>
	DList<T>::BeginUnit::BeginUnit():
	DList<T>::Unit()
	{}

	template <class T>
	DList<T>::EndUnit::EndUnit():
	DList<T>::Unit()
	{}

	template <class T>
	DList<T>::BeginUnit::~BeginUnit()
	{};

	template <class T>
	DList<T>::EndUnit::~EndUnit()
	{};
/*
	template <class T>
	typename DList<T>::Unit*
	DList<T>::BeginUnit::next()
	{
		return __next;
	}

	template <class T>
	typename DList<T>::Unit*
	DList<T>::EndUnit::prev()
	{
		return __prev;
	}
*/
	template <class T>
	bool
	DList<T>::BeginUnit::ok()
	{
		if (next() == NULL)
			return false;
		return true;
	}

	template <class T>
	bool
	DList<T>::EndUnit::ok()
	{
		if (prev() == NULL)
			return false;
		return true;
	
	}

};
