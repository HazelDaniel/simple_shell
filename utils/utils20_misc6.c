#include "main.h"

/**
 * _free - a function that frees
 * a dynamically allocated object
 * safely
 * description: subsequent calls to _free
 * on the same dynamically allocated object
 * will have no effect.
 * @ptr: the address of the dynamically allocated
 * object
 * Return: void
 **/
void _free(void **ptr)
{
	free(*ptr), *ptr = NULL;
}

/**
 * _strvcat - a function that concatenates
 * a variable number of strings
 * @first_str: the first string in the parameter
 * list
 * Return: char *
 **/
char *_strvcat(char *first_str, ...)
{
	va_list arg_list;
	char *curr_str, *acc = NULL, *tmp = NULL;

	va_start(arg_list, first_str);
	curr_str = first_str;
	while (curr_str)
	{
		tmp = _strdcat(acc, curr_str);
		_free_(acc), acc = tmp;
		curr_str = va_arg(arg_list, char *);
	}
	va_end(arg_list);

	return (acc);
}
