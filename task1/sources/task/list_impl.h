/**
 * @file 	task/list_impl.h 
 * @brief	Solution implementation of the programming task 1
 * @author	Sergey Ivanychev, DCAM MIPT
 * 
 * @detailes	There are template list methods are implemented
 */

#include "exception.h"
#include "stdio.h"
//#include "iface.h"

namespace Task
{
	/**
	 * @brief set_next() and set_prev
	 * @details Functions that are only available for list. Dangerous for list health/
	 * 
	 * @param setting Setting up unit
	 * @param new_ptr New next (prev) unit
	 * 
	 * @return void
	 */
	template <class T>
	void
	DList<T>::set_next(Unit* setting, Unit* new_ptr)
	{
		RT_ASSERT(setting != NULL, ARG_PTR_NULL);

		setting -> __next = new_ptr;
	}

	template <class T>
	void
	DList<T>::set_prev(Unit* setting, Unit* new_ptr)
	{
		RT_ASSERT(setting != NULL, ARG_PTR_NULL);
//		RT_ASSERT(new_ptr != NULL, ARG_PTR_NULL);

		setting -> __prev = new_ptr;
	}

/**
 * @brief 	DList template constructor
 */
	template <class T>
	DList<T>::DList():
	__size(0),
	__lborder(NULL),
	__rborder(NULL)
	{}

/**
 * @brief 	DList destructor
 * @details 	Deletes all the Units, because they were constructed dynamically
 * 
 */
	template <class T>
	DList<T>::~DList()
	{
		Unit* deleting = __lborder;
		

		while (deleting != NULL)
		{
			Unit* new_deleting = deleting -> next();
			delete deleting;
			deleting = new_deleting;
		}

		__size = 0;
		__lborder = NULL;
		__rborder = NULL;
	}

/**
 * @brief 	__is_in() private method
 * @details 	Caters searching for SEARCHED element in DList
 * 
 * @param 	searched Searching element
 * @return 	true, if found
 */
	template <class T>
	bool
	DList<T>::__is_in(const Unit* searched)
	{
		Unit* checked = __lborder;
		
//		for (unsigned i = 0; i < __size; ++i)
		while (checked != NULL)
		{
			if (checked == searched)
				return true;
			checked = checked -> next();
		}
		return false;
	}


/**
 * @brief 	Insert()
 * @details 	Inserts newly constructed unit before argumented
 * 
 * @param u	front unit
 * @param val 	value to build new unit
 * 
 * @return 	pointer to the new unit
 */
template <class T>
typename DList<T>::Unit*
DList<T>::insert(typename DList<T>::Unit* u, const T& val)
{
	RT_ASSERT(this -> ok(), PRECOND_SELF_CHECK_FAILED);
	RT_ASSERT(u != NULL, ARG_PTR_NULL);
	RT_ASSERT(__is_in(u), NO_UNIT_IN_LIST);

	Unit* after = u -> prev();
	Unit* before = u;

//		assert(after -> next() == before);
//		assert(before -> prev() == after);

	Unit* inserting = new Unit(val);
	
	if (after != NULL)
	{
		CALL(set_next(after,  inserting), "Setting __next pointer failed");
	}
	
	if (before != NULL)
	{
		CALL(set_prev(before, inserting), "Setting __prev pointed failed");
	}
	
	CALL(set_next(inserting, before), "Setting __next pointer failed");
	CALL(set_prev(inserting, after) , "Setting __prev pointed failed");

	__size++;
	RT_ASSERT(this -> ok(), POSTCOND_SELF_CHECK_FAILED);
	return inserting;
}
//=============================================================================================

/**
 * @brief 	__Init()
 * @details 	Creates new unit and pushes it to list, if it is empty
 * 
 * @param 	val Value to build the unit
 */

template<class T>
void
DList<T>::__init(const T& val)
{
	RT_ASSERT(	__lborder == 0 && 
				__rborder == 0 && 
				__size	  == 0,
				ALREADY_INITED);
	Unit* u = new Unit(val);
	assert(u);

	__lborder = u;
	__rborder = u;
	__size++;
}
//=============================================================================================

/**
 * @brief 	Push_front() and Push_back()
 * @details 	Methods to create new unit and put it on the first or 
 * 		on the last position to the list
 * 
 * @param 	val Value to build unit
 */
template <class T>
void
DList<T>::push_front(const T& val)
{
	if (__size > 0)
	{
		Unit* u = new Unit(val);
		assert(u);
		CALL(set_prev(__lborder, u),   "Failed to set pointers");
		CALL(set_next(u, __lborder), "Failed to set pointers");
		__lborder = u;
		__size++;
	}
	else
	{
	CALL(__init(val), "Initialization of list failed");
	}
}

template <class T>
void
DList<T>::push_back(const T& val)
{
	if (__size > 0)
	{
		Unit* u = new Unit(val);
		assert(u);
		CALL(set_next(__rborder, u),   "Failed to set pointers");
		CALL(set_prev(u, __rborder), "Failed to set pointers");
		__rborder = u;
		__size++;
	}
	else
	{
	CALL(__init(val), "Initialization of list failed");
	}
}
//=============================================================================================

/**
 * @brief 	Erase()
 * @details 	Erases argumented unit from the list
 * 
 * @param u 	Unit to delete
 * @return 	Pointer to the next unit
 */
template <class T>
typename DList<T>::Unit*
DList<T>::erase(Unit* u)
{
	RT_ASSERT(u != NULL, ARG_PTR_NULL);
	RT_ASSERT(__is_in(u), NO_UNIT_IN_LIST);

	DList<T>::Unit* next_unit = u -> next();
	DList<T>::Unit* prev_unit = u -> prev();
	if (prev_unit != NULL)
	{
	CALL(set_next(prev_unit, next_unit), "Failed to set pointers");
	} 
	else
	{
		__lborder = u -> next();
	}

	if (next_unit != NULL)
	{
	CALL(set_prev(next_unit, prev_unit), "Failed to set pointers");
	}
	else
	{
		__rborder = u -> prev();
	}
	__size--;

	delete u;
	return next_unit;
}
//=============================================================================================

/**
 * @brief 	Pop_front() and pop_back() methods
 * @details 	erase the first or the last unit
 * 
 */
template <class T>
void
DList<T>::pop_front()
{
	RT_ASSERT(__lborder != NULL, EMPTY_LIST);
	CALL(erase(__lborder), "Failed to erase first element");
}

template <class T>
void
DList<T>::pop_back()
{
	RT_ASSERT(__rborder != NULL, EMPTY_LIST);
	CALL(erase(__rborder), "Failed to erase last element");
}
//=============================================================================================

/**
 * @brief 	First(), last()
 * @details 	retrun the pointer to the first or to the last unit in list
 * 
 */
template <class T>
typename DList<T>::Unit*
DList<T>::first()
{
	return __lborder;
}
//=============================================================================================

template <class T>
typename DList<T>::Unit*
DList<T>::last()
{
	return __rborder;
}
//=============================================================================================

/**
 * @brief 	Clear()
 * @details 	Clears the whole list to its defaults
 * 
 */
template <class T>
void
DList<T>::clear()
{
	this -> ~DList();
	DList();
}
//=============================================================================================

/**
 * @brief Empty() method
 * @details Returns, whether the list is empty or not
 * 
 */
template <class T>
bool
DList<T>::empty()
{
	return (__size == 0)? true: false;
}
//=============================================================================================

/**
 * @brief 	Size()
 * @details 	Returns the ammount of units in list
 *  
 **/
template <class T>
unsigned
DList<T>::size()
{
	return __size;
}
//=============================================================================================

/**
 * @brief 	__swap_next_prev()
 * @details 	swaps __next and __prev pointers in argumented unit
 * 
 * @param u 	Changing unit
 */
template <class T>
void		
DList<T>::__swap_next_prev(Unit* u)
{
	assert(u);
	Unit* temp = u -> __next;
	u -> __next = u -> __prev;
	u -> __prev = temp;
}
//=============================================================================================

/**
 * @brief Reverse()
 * @details Changes the order of units to opposite
 * 
 */
template <class T>
void
DList<T>::reverse()
{
	RT_ASSERT(this -> ok(), PRECOND_SELF_CHECK_FAILED);
	DList<T>::Unit* temp = NULL;

	if (__size == 0)
		return;

	temp = __lborder;
	__lborder = __rborder;
	__rborder = temp;

	DList<T>::Unit* changing = __lborder;

	while (changing != NULL)
	{
		__swap_next_prev(changing);
		changing = changing -> next();
	}
	RT_ASSERT(this -> ok(), PRECOND_SELF_CHECK_FAILED);	
}
//=============================================================================================

/**
 * @brief Dump()
 * @details Provides detailed dump of structure to the argumented stream
 * 
 * @param stream Output file stream
 */
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
					(ok())?"OK":"BAD",
					__size,
					__lborder,
					__rborder);
	DList<T>::Unit* printing = __lborder;
	for (unsigned i = 0; i < __size; ++i)
	{
		assert(printing);
		printing -> dump(stream);
		fprintf(stream, "\n |\n |\n");
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
//=============================================================================================
/**
 * @brief Ok()
 * @details Checks the health of list
 * 
 * @return true, if the list is valid
 */
template <class T>
bool
DList<T>::ok()
{
	if ( (__lborder || __rborder) && __size == 0) 
		return false;
	if (!(__lborder && __rborder) && __size != 0) 
		return false;
	if (__size == 0) 
		return true;
	
	DList<T>::Unit* checked = __lborder;
	for (unsigned i = 0; i < __size; ++i)
	{
		if (checked -> ok() == false)
			return false;
		if (checked -> prev() && checked -> prev() -> next() != checked)
			return false;
		if (checked -> next() && checked -> next() -> prev() != checked)
			return false;
		checked = checked -> next();
	}
	if (checked != NULL)
		return false;
	return true;
}
};
