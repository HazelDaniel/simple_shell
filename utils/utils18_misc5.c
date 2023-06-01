#include "main.h"

/**
* is_dot - a function that checks if
* a character is a logical operator
* @c: parameter of type char .
* Return: int .
*/
int is_log(char c)
{
	if (c == '|' || c == '&')
		return (1);
	return (0);
}

/**
* is_n_var - a function that checks if
* a character can't be included in a variable
* @c: parameter of type char .
* Return: int .
*/
int is_n_var(char c)
{
	return ((!is_word(c) && c != '$'));
}

/**
 * _memset - a function that sets
 * contigious memory blocks to a value
 * @ptr: the address of the first element in the
 * memory block
 * @val: the value
 * @len: the length of the assignment
 * Return: void
 * description: checked
 **/
void _memset(void *ptr, int val, size_t len)
{
	size_t i;
	char *ptr_mut = (char *)ptr;

	for (i = 0; i < len; i++)
		ptr_mut[i] = val;
}

/**
  * in_str - a function that looks up
	* a character in a string and returns
	* a boolean integer if found
  * @c: parameter of type char .
  * @str: parameter of type char *.
  * Return: int .
	* description: checked
 */
int in_str(char c, char *str)
{
	int i = 0;

	if (!str)
		return (0);

	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/**
 * _strcpy - a function that copies the contents
 * of the source string to the destination string
 * @dest: destination string
 * @src: source string
 * Return: char *
 * description: checked
 **/
char *_strcpy(char (*dest)[BUFF_LEN], char **src)
{
	size_t i;

	if (!src || !src[0])
		return (NULL);
	for (i = 0; (*src)[i] != '\0'; i++)
		(*dest)[i] = (*src)[i];
	(*dest)[i] = '\0';
	return ((*dest));
}
