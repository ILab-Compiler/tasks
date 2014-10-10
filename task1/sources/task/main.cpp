
#include "iface.h"

using namespace Task;

int tmain();

int main()
{
	try
	{
		tmain();
	}
	catch(ivException& exc)
	{
		exc.listed_report(cout);
		exc.listed_delete();
		return 0;
	}
	return 0;
}

int tmain()
{
	DList<int> int_list;
	int_list.dump();
	int_list.push_front(3);
	int_list.push_front(2);
	int_list.push_front(1);
	int_list.dump();

	return 0;
}
