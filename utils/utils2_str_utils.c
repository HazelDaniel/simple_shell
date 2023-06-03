#include "main.h"

/**
  * _strcmp - a function that compares two strings
  * @str1: parameter of type char *
  * @str2: parameter of type char *
  * Return: an integer value
	* description: 0 if str1 == str2
	*              len(str1) - len(str2) if str1 != str2
	*
	* checked
 */
int _strcmp(char *str1, char *str2)
{
	int count, i, len1 = _strlen(str1), len2 = _strlen(str2);

	if (!str1 && !str2)
		return (0);
	if (!str1 && str2)
		return (len2);
	if (str1 && !str2)
		return (len1);
	count = 0;
	if (str1[count] != str2[count])
		return (len1 + len2);

	while (str1[count] == str2[count] && (str2[count] && str1[count]))
		count++;
	if (!str1[count] && !str2[count])
		return (0);
	if (str1[count] && str2[count])
		return (find_max(len1, len2) - count);
	i = 0;
	if (str1[count] && !str2[count])
	{
		while (str1[count])
			count++, i++;
		return (i);
	}
	if (!str1[count] && str2[count])
	{
		while (str2[count])
			count++, i++;
		return (-i);
	}
	return (count);/* not needed all paths handled already */
}

/**
 * _strlen - a function that computes
 * the lenght of a string
 * @str: the string
 * Return: unsigned int
 * description: checked
 **/
unsigned int _strlen(char *str)
{
	int len = 0;

	if (!str)
		return (len);
	while (str[len])
		len++;

	return (len);
}

/**
* _strncat - A function that concatenates two strings
* up to a specified length
* @dest: a destination string
* @src: a string to append
* @n: the specified length
* Return: Always a string
* description: checked
**/
char *_strncat(char *dest, char *src, int n)
{
	int ind = 0, i;
	unsigned int res_len = 0;
	char *res = NULL;

	res_len = _strlen(src) + _strlen(dest);

	res = malloc((res_len) * sizeof(char) + 1);
	if (!res)
		return (res);
	if (res_len == 0)
		return (NULL);
	res[res_len] = '\0';

	for (ind = 0; dest && dest[ind]; ind++)
		res[ind] = dest[ind];
	for (i = 0; i < n && src && src[i]; ind++, i++)
		res[ind] = src[i];

	return (res);
}
/**
* _strdcat - A function that concatenates two strings
* dynamically
* @dest: a destination string
* @src: a string to append
* description: the first string and only that needs to be
*     dynamically allocated
*     checked
* Return: Always a string
**/
char *_strdcat(char *dest, char *src)
{
	int dest_count = 0, src_count = 0, ind = 0;
	unsigned int res_len = 0, i, dest_len, src_len;
	char *res = NULL;

	dest_len = _strlen(dest), src_len = _strlen(src);
	res_len = dest_len + src_len;

	res = malloc((res_len) * sizeof(char) + 1);
	if (!res)
		return (res);
	if (res_len == 0)
		return (NULL);
	res[res_len] = '\0';

	for (ind = 0; ind < dest_len; ind++)
		res[ind] = dest[ind];
	for (i = 0; ind < res_len; ind++)
		res[ind] = src[i++];

	return (res);
}

/**
 * _log_split - a function that logically splits a string
 * into an array of strings based on a delimiter
 * @str: the input string
 * @delim: the delimiter
 * Return: char **
 * description: checked
 **/
char **_log_split(char *str, char *delim)
{
	char **res_str = NULL, *token, *res_buff[1024] = {NULL},
	*trimmed = _trim(str);
	size_t count = 0, res_index = 0, i = 0;

	if (!trimmed)
		return (NULL);
	token = com_tok(trimmed, delim);
	while (token)
	{
		count = 0;
		while (token[count])
			count++;
		res_buff[res_index] = malloc((count * sizeof(char)) + 1);
		if (!res_buff[res_index])
		{
			for (i = 0; i < res_index; i++)
				_free_(res_buff[i]), _free_(trimmed);
			return (NULL);
		}
		res_buff[res_index][count] = '\0';
		for (i = 0; token[i]; i++)
			res_buff[res_index][i] = token[i];
		token = com_tok(NULL, delim);
		res_index++;
	}
	empty_state_buff(delim);
	res_str = malloc((res_index) * sizeof(char *) + sizeof(char *));
	if (res_str == NULL)
	{
		free_str_arr(res_buff, 0), _free_(trimmed);
		return (NULL);
	}
	res_str[res_index] = NULL;
	for (i = 0; i < res_index; i++)
		res_str[i] = res_buff[i];
	_free_(trimmed);

	return (res_str);
}
