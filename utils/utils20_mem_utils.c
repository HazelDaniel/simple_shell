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
