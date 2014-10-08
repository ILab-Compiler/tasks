/**
 * @file: task/unit_impl.h 
 * Solution implementation of the programming task 1
 */

#include "exception.h"
#include "stdio.h"
#include "iface.h"

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
	DList<T>::Unit::Unit(const &T val):
	Unit()
	{
		CALL(__val = new T(val), ARG_OBJ_COPY_FAIL);
		RT_ASSERT(__val != NULL, ARG_OBJ_COPY_FAIL);

		__empty = false;
	}

	template <class T>
	DList<T>::?Unit::~Unit()
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
		return __next;
	}

	template <class T>
	typename DList<T>::Unit*
	DList<T>::Unit::prev()
	{
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
		fprintf(stream, "Unit [%08x]"
						"__empty = %s"
						"__val  = [%08x]"
						"__prev = [%08x]"
						"__next = [%08x]",
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

	template <class T>
	typename DList<T>::Unit*
	DList<T>::BeginUnit::next()
	{
		return __next;
	}

	template <class T>
	typename DList<T>::Unit*
	DList<T>::EndUnit::next()
	{
		return __prev;
	}

	template <class T>
	bool
	DList<T>::BeginUnit::ok()
	{
		if (__next == NULL)
			return false;
		if (__val == NULL)
			return false;
		return true;
	}

	template <class T>
	bool
	DList<T>::EndUnit::ok()
	{
		if (__prev == NULL)
			return false;
		if (__val == NULL)
			return false;
		return true;
	
	}

};