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
	char *buff = NULL, *res = NULL, *slash = NULL, *tmp, *path;
	int dir_len, input_len;

	slash = "/";
	while (current)
	{
		dir_len = _strlen(current->dir), input_len = _strlen(input);
		buff = _strvcat(current->dir, slash, input, NULL);
		if (buff && access(buff, F_OK) == 0)
			return (buff);
		_free_(buff);
		buff = NULL;
		current = current->next;
	}
	return (NULL);
}
