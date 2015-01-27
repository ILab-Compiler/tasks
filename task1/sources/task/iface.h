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

/**
 * Namespace for the programming task
 */
namespace Task
{
    //
    // Doubly connected list
    //
    template <class T> class DList
    {
    public:
        //
        // List unit
        //
        class Unit
        {
        public:
            // ---- This interface is part of the task ---
            Unit *next() // Get the next unit in list
			{
					return next;
			}
            Unit *prev() // Get the previous unit in list
			{
				return prev;
			}
            T& val()     // Get the reference to the unit's value
			{
				return &value;
			}
        private:
        // ---- Implementation routines ----
			T value;
			Unit *next, *prev;
            

			//
        // ---- Data involved in the implementation ----    
         
        };

        // ---- Public interface of DList ----
        DList(): head(NULL) , tail(NULL) , count(0) {}; //< Constructor
        ~DList()//< Destructor
		{
			while (head) //Пока по адресу на начало списка что-то есть
			{
				tail = head->next; //Резервная копия адреса следующего звена списка
				delete head; //Очистка памяти от первого звена
				head = tail; //Смена адреса начала на адрес следующего элемента
			}
			delete count;
		}
        
        void push_front (const T& val)       // Insert one unit with given value at front
		{
			count++;
			if (empty() != 0))
			{
				 Unit *node_to_add = new Unit(val);
				 node_to_add->next = head;
				 node_to_add->prev = 0;
				 node_to_add->value = val;
				 head->prev = node_to_add;
			}
			else
			{
				Unit *node_to_add = new Unit(val);
				node_to_add->next = tail;
				node_to_add->prev = tail->prev;
				node_to_add->value = val;
				tail->prev->next = node_to_add;
				tail->prev = node_to_add;
			}
		}       
        void pop_front()                     // Remove one unit at front of the list
		{
			count--;
			cout << head->value;
			 if (val != NULL)  // проверка корректности
			 {
				 val = head;
				 head = val->next;
				 delete(val);
				 head->prev = 0;
				 val = head;
			 }
		}
        void push_back (const T& val)       // Insert one unit with given value to back
		{
			count++;
			if (empty() != 0))
			{
				 Unit *node_to_add = new Unit(val);
				 node_to_add->next = 0;
				 node_to_add->prev = tail;
				 node_to_add->value = val;
				 tail->next = node_to_add;
			}
			else
			{
				Unit *node_to_add = new Unit(val);
				node_to_add->next = tail;
				node_to_add->prev = tail->prev;
				node_to_add->value = val;
				
				tail->prev->next = node_to_add;
				tail->prev = node_to_add;
			}
		}       
        void pop_back()                      // Remove one unit from the back of the list
		{
			count--;
			cout << tail->value;
			val = tail;
			 if (val->next == NULL) // проверка корректности
			 {
				 val->prev->next = NULL;
				 delete(val);
				 val = head;
			 }
		}
        Unit* insert (Unit* u, const T& val) // Insert one unit before the given one
		{
			count++;
			Unit *node_to_add = new Unit(val);
			if (empty() == 0)
			{
				node_to_add->next = tail;
				node_to_add->prev = tail->prev;
				node_to_add->value = val;
				tail->prev->next = node_to_add;
				tail->prev = node_to_add;
			}
			else
			{
				node_to_add->next = u;
				node_to_add->prev = u->prev;
				node_to_add->value = val;
				u->prev->next = node_to_add;
				u->next->prev = node_to_add;
			}
		}

        Unit* first() // Get first unit
		{
				return head;
		}
        Unit* last()  // Get last unit
		{
				return tail;
		}
        
        Unit* erase (Unit* u) // Remove given unit from list, return next unit or null
		{
			count--;
			Unit *ptr; // вспомогательный указатель
			ptr = u->next;
			if (u == head)
			{
				if (val != NULL)  // проверка корректности
			 {
				 val = u;
				 head = val->next;
				 delete(val);
				 head->prev = 0;
				 val = head;
			 }
				return ptr;
			}
			if (u == tail)
			{
				val = u;
				if (val->next == NULL) // проверка корректности
				{
					val->prev->next = NULL;
					delete(val);
					val = head;
				}
				return ptr;
			}
			else 
			{
				val = u;
				val->prev->next = val->next->prev;
				delete(val);
				val = head;
				return ptr;
			}

		}
        void clear()          // Remove all units
		{
			while (head) //
			{
				tail = head->Next; //
				delete head; //
				head = tail; //
			}
			head = NULL;
			tail = NULL;
			count = 0;
		}
        bool empty()          // Check if list is empty. Returns true if empty, false otherwise
		{
			return count;
		}
        unsigned size()       // Get the number of units in the list
        {
			return count;
		}
		void reverse()        // Reverse the order of units in the list
		{
			val = head;
			while( val->next != NULL)
			{
				tail->prev->next = NULL;
				head->next = head;
				head->prev = 0;
				head = tail;
				tail = tail->prev;
				val = head->next;
			}
		}
private:
        // ---- The internal implementation routines ----
        int count;
		Unit *val; //текущий элемент
		Unit *head;
		Unit *tail;
        // ---- The data involved in the implementation ----
       
    };


    bool uTest( UnitTest *utest_p);
};

// Since we have defined list as a template - we should implement the solution in a header
// But to keep interface clean we've separated the implementation into list_impl.h header
#include "list_impl.h"

