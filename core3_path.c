#include "utils/main.h"

/**
  * _trace -  a function that returns
	* first location it finds of an input
	* command file
  * @input: parameter of type char *.
  * Return: char *.
 */
char *_trace(char *input)
{
	pathdir_t *current = path_list;
	char *buff = NULL, *slash = NULL;

	slash = "/";
	while (current)
	{
		buff = _strvcat(current->dir, slash, input, NULL);
		if (buff && access(buff, F_OK) == 0)
			return (buff);
		_free_(buff);
		buff = NULL;
		current = current->next;
	}
	return (NULL);
}
