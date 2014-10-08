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
	void
	DList<T>::set_next(Unit* setting, Unit* new_ptr)
	{
		RT_ASSERT(setting != NULL, ARG_PTR_NULL);
		RT_ASSERT(new_ptr != NULL, ARG_PTR_NULL);

		setting -> __next = new_ptr;
	}

	template <class T>
	void
	DList<T>::set_prev(Unit* setting, Unit* new_ptr)
	{
		RT_ASSERT(setting != NULL, ARG_PTR_NULL);
		RT_ASSERT(new_ptr != NULL, ARG_PTR_NULL);

		setting -> __prev = new_ptr;
	}


	template <class T>
	DList<T>::DList():
	__size(0)
	{
		set_next((typename DList<T>::Unit*)&__lborder, (typename DList<T>::Unit*)&__rborder);
		set_prev((typename DList<T>::Unit*)&__rborder, (typename DList<T>::Unit*)&__lborder);
		assert(this -> ok());
	}

	template <class T>
	DList<T>::~DList()
	{
		DList<T>::Unit* deleting = __lborder.next();
		assert(deleting);

		while (deleting != (DList<T>::Unit*)&__rborder)
		{
			DList<T>::Unit* new_deleting = deleting -> next();
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
		DList<T>::Unit* checked = __lborder.next();
		assert(checked);

		for (unsigned i = 0; i < __size; ++i)
		{
			checked = checked -> next();
			assert(checked);
			if (checked == searched)
				return true;
		}

		return false;
	}


	template <class T>
	typename DList<T>::Unit*
	insert (typename DList<T>::Unit* u, const T& val)
	{
		RT_ASSERT(this -> ok(), PRECOND_SELF_CHECK_FAILED);
		RT_ASSERT(u != NULL, ARG_PTR_NULL);
		RT_ASSERT(__is_in(u), NO_UNIT_IN_LIST);

		DList<T>::Unit* after = u -> prev;
		DList<T>::Unit* before = u;

		assert(after -> next() == before);
		assert(before -> prev() == after);

		DList<T>::Unit* inserting = new Unit(val);
		
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
	DList<T>::push_back(const T& val)
	{
		DList<int>::Unit* needed_ptr = (DList<T>::Unit*)(&__rborder);
		CALL(insert(__lborder.next(), val), "Inserting first element failed");
	}

	template <class T>
	void
	DList<T>::push_front(const T& val)
	{
		DList<int>::Unit* needed_ptr = __lborder.next();
		CALL(insert(__lborder.next(), val), "Inserting first element failed");
	}

	

	template <class T>
	typename DList<T>::Unit*
	DList<T>::erase(Unit* u)
	{
		RT_ASSERT(u != NULL, ARG_PTR_NULL);
		RT_ASSERT(__is_in(u), NO_UNIT_IN_LIST);

		DList<T>::Unit* next_unit = u -> next();
		DList<T>::Unit* prev_unit = u -> prev();
		CALL(set_next(prev_unit, next_unit), "Failed to set pointers");
		CALL(set_prev(next_unit, prev_unit), "Failed to set pointers");
		__size--;

		delete u;
		return (next_unit == (DList<T>::Unit*)&__rborder)? NULL: next_unit;
	}

	template <class T>
	void
	DList<T>::pop_front()
	{
		DList<T>::Unit* erasing = __lborder.next();
		RT_ASSERT(erasing != (DList<T>::Unit*)&__rborder, EMPTY_LIST);
		CALL(erase(__lborder.next()), "Failed to erase first element");
	}

	template <class T>
	void
	DList<T>::pop_back()
	{
		DList<T>::Unit* erasing = __rborder.prev();
		RT_ASSERT(erasing != __lborder, EMPTY_LIST);
		CALL(erase(erasing), "Failed to erase last element");
	}

	template <class T>
	typename DList<T>::Unit*
	DList<T>::first()
	{
		RT_ASSERT(ok(), PRECOND_SELF_CHECK_FAILED);
		if (__size > 0) return __lborder.next();
		return NULL;
	}

	template <class T>
	typename DList<T>::Unit*
	DList<T>::last()
	{
		RT_ASSERT(ok(), PRECOND_SELF_CHECK_FAILED);
		if (__size > 0) return __rborder.prev();
		return NULL;
	}

	template <class T>
	void
	DList<T>::clear()
	{
		this -> ~DList();
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
		RT_ASSERT(this -> ok(), PRECOND_SELF_CHECK_FAILED);
		DList<T>::Unit* temp = NULL;

		if (__size == 0)
			return;

		temp = __lborder.next();
		CALL(set_next((DList<T>::Unit*)&__lborder, __rborder.prev()),	"Failed setting pointers");
		CALL(set_prev((DList<T>::Unit*)&__rborder, temp),					"Failed setting pointers");
		
		DList<T>::Unit* changing = (DList<T>::Unit*)&__lborder;

		for (unsigned i = 0; i < size(); ++i)
		{
			assert(changing -> next());
			changing = changing -> next();

			temp = changing -> prev();
			CALL(set_prev(changing, changing -> next()),"Failed setting pointers");
			CALL(set_next(changing, temp),				"Failed setting pointers");
		}
		RT_ASSERT(this -> ok(), PRECOND_SELF_CHECK_FAILED);	
	}

	template <class T>
	void
	DList<T>::dump(FILE* stream)
	{
		fprintf(stream,	"List [%08x]\n"
						"Status %s\n"
						"Size = %ud\n"
						"Left border  [%08x]\n"
						"Right border [%08x]\n"
						"Calling units dump\n |\n |\n",
						this,
						(ok()):"OK":"BAD");
		DList<T>::Unit* printing = __lborder.next();
		for (int i = 0; i < size; ++i)
		{
			assert(printing);
			printing -> dump(stream);
			fprintf("\n |\n |\n");
			printing = printing -> next();
		}
		fprintf(stream, "List dump finished\n");
	}


	template <class T>
	void
	DList<T>::dump()
	{
		dump(stdout);
	}

	template <class T>
	bool
	DList<T>::ok()
	{
		if (__lborder.next() == NULL) return false;
		if (__rborder.prev() == NULL) return false;

		DList<T>::Unit* checked = (DList<T>::Unit*)&__lborder;
		if (checked == 0) return false;
		for (unsigned i = 0; i < size(); ++i)
		{
			if (checked -> next() == NULL) 
				return false;
			checked = checked -> next();
			if (checked -> ok() == false)
				return false;
			if (checked -> next() == NULL)
				return false;
			if (checked -> prev() -> next() != checked)
				return false;
			if (checked -> next() -> prev()  != checked)
				return false;
		}
		if (checked != (DList<T>::Unit*)&__rborder)
			return false;
		return true;
	}
};
