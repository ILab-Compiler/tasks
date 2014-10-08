/**
 * @file: task/list_impl.h 
 * Solution implementation of the programming task 1
 */

#include "exception.h"
#include "stdio.h"
//#include "iface.h"

namespace Task
{

	template <class T>
	DList<T>::set_next(Unit* setting, Unit* new_ptr)
	{
		RT_ASSERT(setting != NULL, ARG_PTR_NULL);
		RT_ASSERT(new_ptr != NULL, ARG_PTR_NULL);

		setting -> __next = new_ptr;
	}

	template <class T>
	DList<T>::set_prev(Unit* setting, Unit* new_ptr)
	{
		RT_ASSERT(setting != NULL, ARG_PTR_NULL);
		RT_ASSERT(new_ptr != NULL, ARG_PTR_NULL);

		setting -> __prev = new_ptr;
	}


	template <class T>
	DList<T>::DList():
	__size(0),
	{
		set_next(&__lborder, &__rborder);
		set_prev(&__rborder, &__lborder);
		assert(this -> ok());
	}

	template <class T>
	DList<T>::~DList()
	{
		Unit* deleting = __lborder -> next();
		assert(deleting);

		while (deleting != __rborder)
		{
			Unit* new_deleting = deleting -> next();
			assert(new_deleting);
			delete deleting;
			deleting = new_deleting;
		}

		__size = 0;
	}

	template <class T>
	bool
	DList<T>::__is_in(const Unit* searched)
	{
		Unit* checked = __lborder -> next();
		assert(checked);

		for (int i = 0; i < __size; ++i)
		{
			checked = checked -> next();
			assert(checked);
			if (checked = searched)
				return true;
		}

		return false;
	}


	template <class T>
	typename DList<T>::Unit*
	insert (Unit* u, const T& val)
	{
		RT_ASSERT(this -> ok(), PRECOND_SELF_CHECK_FAILED);
		RT_ASSERT(u != NULL, ARG_PTR_NULL);
		RT_ASSERT(__is_in(u), NO_UNIT_IN_LIST);

		Unit* after = u -> prev;
		Unit* before = u;

		assert(after -> next() == before);
		assert(before -> prev() == after);

		Unit* inserting = new Unit(val);
		
		CALL(set_next(after,  inserting), "Setting __next pointer failed");
		CALL(set_prev(before, inserting), "Setting __prev pointed failed");
		CALL(set_next(inserting, before), "Setting __next pointer failed");
		CALL(set_prev(inserting, after) , "Setting __prev pointed failed");

		__size++;
		RT_ASSERT(this -> ok(), POSTCOND_SELF_CHECK_FAILED);
		return inserting;
	}

	template <class T>
	void
	DList<T>::push_front(const T& val)
	{
		CALL(insert(val, __lborder -> next()), "Inserting first element failed");
	}

	template<class T
	void
	DList<T>::push_back(const T& val)
	{
		CALL(insert(val, __rborder), "Inserting last element failed");
	}

	template <class T>
	typename DList<T>::Unit*
	DList<T>::erase(Unit* u)
	{
		RT_ASSERT(u != NULL, ARG_PTR_NULL);
		RT_ASSERT(__is_in(u), NO_UNIT_IN_LIST);

		Unit* next_unit = u -> next();
		Unit* prev_unit = u -> prev();
		CALL(set_next(prev_unit, next_unit), "Failed to set pointers");
		CALL(set_prev(next_unit, prev_unit), "Failed to set pointers");
		__size--;

		delete u;
		return (next_unit == __rborder)? NULL: next_unit;
	}

	template <class T>
	void
	DList<T>::pop_front()
	{
		Unit* erasing = __lborder -> next();
		RT_ASSERT(erasing != __rborder, EMPTY_LIST);
		CALL(erase(__lborder -> next()), "Failed to erase first element");
	}

	template <class T>
	void
	DList<T>::pop_back()
	{
		Unit* erasing = __rborder -> prev();
		RT_ASSERT(erasing != __lborder, EMPTY_LIST);
		CALL(erase(erasing), "Failed to erase last element");
	}

	template <class T>
	typename DList<T>::Unit*
	DList<T>::first()
	{
		RT_ASSERT(ok(), PRECOND_SELF_CHECK_FAILED);
		if (__size > 0) return __lborder -> next();
		return NULL;
	}

	template <class T>
	typename DList<T>::Unit*
	DList<T>::last()
	{
		RT_ASSERT(ok(), PRECOND_SELF_CHECK_FAILED);
		if (__size > 0) return __rborder -> prev();
		return NULL;
	}

	template <class T>
	void
	DList<T>::clear()
	{
		~DList();
		 DList();
	}

	template <class T>
	bool
	DList<T>::empty()
	{
		RT_ASSERT(ok(), PRECOND_SELF_CHECK_FAILED);
		return (__size == 0)? true: false;
	}

	template <class T>
	unsigned
	DList<T>::size()
	{
		RT_ASSERT(ok(), PRECOND_SELF_CHECK_FAILED);
		return __size;
	}

	template <class T>
	void
	DList<T>::reverse()
	{
		RT_ASSERT(ok(), PRECOND_SELF_CHECK_FAILED);
		Unit* temp = NULL;

		if (__size == 0)
			return;

		temp = __lborder -> next();
		CALL(set_next(__lborder, __rborder -> prev()),	"Failed setting pointers");
		CALL(set_prev(__rborder, temp),					"Failed setting pointers");
		
		Unit* changing = __lborder;

		for (int i = 0; i < size; ++i)
		{
			assert(changing -> next());
			changing = changing -> next();

			temp = changing -> prev();
			CALL(set_prev(changing, changing -> next()),"Failed setting pointers");
			CALL(set_next(changing, temp),				"Failed setting pointers");
		}
		RT_ASSERT(ok(), PRECOND_SELF_CHECK_FAILED);	
	}
};
