#ifndef __MESSAGES_HEADER
#define __MESSAGES_HEADER

enum MESSAGE_ID
{
	FIRST_ID = 1000,
	ARG_OBJ_COPY_FAIL,
	NO_VALUE_IN_OBJ,
	ARG_PTR_NULL,
	NO_UNIT_IN_LIST,
	PRECOND_SELF_CHECK_FAILED,
	POSTCOND_SELF_CHECK_FAILED,
	EMPTY_LIST,
	LAST_ID
}

const char* const msgs[] = 
{
	"",
	"Failed to copy argumented object",
	"No requested value in object",
	"Argumented pointer is NULL",
	"No such unit in current list",
	"Precondition self checking failed",
	"Postcondition self checking failed",
	"List is already empty",
	"",
};


#endif  __MESSAGES_HEADER