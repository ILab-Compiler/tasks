#ifndef _IFACE_HEADER
#define _IFACE_HEADER
/**
 * @file: 	task/iface.h 
 * @author	Sergey Ivanychev, DCAM MIPT
 * 
 * @brief	Descriptions of DList<> and DList<>::Unit classes 
 */
#include "../Utils/utils_iface.h"
#include "exception.h"
#include "messages.h"

/* namespaces import */
using namespace Utils;

//Debug assert with diagnostic info
#if !defined(DLIST_ASSERTXD)
#    define DLIST_ASSERTXD(cond, what) ASSERT_XD(cond, "DList", what)
#endif

// Simple debug assert
#if !defined(DLIST_ASSERTD)
#    define DLIST_ASSERTD(cond) ASSERT_XD(cond, "DList", "")
#endif



namespace Task
{
/**
 * @brief   DList is the template list class we are implementing.
 * @details There are some necessary methods added, such as ok(), dump(), swap()
 * 
 */
    template <class T> class DList
    {
    public:

	class		Unit;
	class		BeginUnit;
	class		EndUnit;
        
        
			DList(); 
		       ~DList();

        void		push_front (const T& val);
        void		pop_front();
        void		push_back (const T& val); 
        void		pop_back();               
        Unit*		insert (Unit* u, const T& val);

        Unit*		first(); 
        Unit*		last();  
        void		set_next(Unit* setting, Unit* new_ptr);
	void		set_prev(Unit* setting, Unit* new_ptr);
	friend void swap(Unit** ptr1, Unit** ptr2);

        Unit*		erase (Unit* u);
        void		clear();  
        bool		empty();         
        unsigned	size();      
        void		reverse();
//	Some extra nesessary features
	void		dump(FILE* stream);
	void		dump();
	bool		ok();
private:
        
	
	unsigned	__size;
	Unit*		__lborder;
	Unit*		__rborder;
	void		__init(const T& val);
	bool		__is_in(const Unit* searched);
	void		__swap_next_prev(Unit* u);
        
        
       
    };

    bool uTest( UnitTest *utest_p);

	template<class T>
	class DList<T>::Unit
	{
public:

			Unit(const T& val);
			Unit();
			~Unit();
	Unit*		next();
	Unit*		prev();
	T&		val();
	friend void 	swap(Unit** ptr1, Unit** ptr2);
			
	void		dump();
	void		dump(FILE* stream);
	virtual bool 	ok();

	friend void	DList<T>::set_next(Unit* setting, Unit* new_ptr);
	friend void	DList<T>::set_prev(Unit* setting, Unit* new_ptr);
	friend void	DList<T>::__swap_next_prev(Unit* u);
private:
				
	bool		__empty;
	T*		__val;
	Unit*		__prev;
	Unit*		__next;
};


};

	#include "list_impl.h"
	#include "unit_impl.h"

#endif