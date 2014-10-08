/**
 * @file: task/iface.h 
 * Interface of a programming task
 */
#include "../Utils/utils_iface.h"

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

    template <class T> class DList
    {
    public:

        class		Unit;
        
        
					DList(); 
				   ~DList();

        void		push_front (const T& val);
        void		pop_front();
        void		push_back (const T& val); 
        void		pop_back();               
        Unit*		insert (Unit* u, const T& val);

        Unit*		first(); 
        Unit*		last();  
        
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
        class		BeginUnit;
		class		EndUnit;
	
		unsigned	__size;
		BeginUnit	__rborder;
		EndUnit		__lborder;
		
		bool		__is_in(const Unit* searched);
		
        
       
    };

    bool uTest( UnitTest *utest_p);

	template<class T>
	class DList<T>::Unit
	{
	public:

					Unit(const &T val);
				   ~Unit();
		Unit*		next();
		Unit*		prev();
		T&			val();
			
		void		 dump();
		void		 dump(FILE* stream);
		virtual bool ok();

		void		set_next(Unit* setting, Unit* new_ptr);
		void		set_prev(Unit* setting, Unit* new_ptr);
	private:
					Unit();
		bool		__empty;
		T*			__val;
		Unit*		__prev;
		Unit*		__next;
	};

	template<class T>
	class DList<T>::BeginUnit: private Unit
	{        
	public:
				
		Unit*		next();
					BeginUnit();
				   ~BeginUnit();
		virtual bool ok();

		friend void DList<T>::set_next(Unit* setting, Unit* new_ptr);

	private:
		Unit const*	__prev;
		Unit*		__next;
	};

	template<class T>
	class DList<T>::EndUnit: private Unit
	{        
	public:
				
		Unit*		prev();
					EndUnit();
				   ~EndUnit();
		virtual bool ok();

		friend void DList<T>::set_prev(Unit* setting, Unit* new_ptr);

	private:
		Unit		__prev;
		Unit const* __next;
	};
};

// Since we have defined list as a template - we should implement the solution in a header
// But to keep interface clean we've separated the implementation into list_impl.h header
#include "list_impl.h"

