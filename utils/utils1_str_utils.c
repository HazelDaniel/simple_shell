#include "main.h"

/**
 * determine_jump - a helper function for my com_tok
 * function that determines whether the logical separator
 * has exact occurrence of two. if it doesn't it skips it
 * @buff_ptr: a pointer to the main buffer
 * @delim: the delimiter
 * @ind_ptr: the pointer to the index
 * @i_ptr: the pointer to the counter
 * Return: void
 * description: checked
 **/
static void determine_jump(char **buff_ptr, char *delim, int *ind_ptr, int *i_ptr)
{
	int noc = -1, lb = 0, acn = 0;

	noc = first_oc_of(*buff_ptr + *i_ptr, *delim);
	if (noc < 0)
		lb = 0;
	acn = adj_char_num(*buff_ptr + *i_ptr + noc, (*buff_ptr)[*i_ptr + noc], 0);
	if (noc >= 0 && acn != 2)
		lb = 1, *i_ptr += (noc + acn), *ind_ptr += (noc + acn);
	if (lb)
	{
		for (*i_ptr = *ind_ptr; (*buff_ptr)[*i_ptr] &&
		!in_str((*buff_ptr)[*i_ptr], delim); (*i_ptr)++)
			(*ind_ptr)++;
	}

}
/**
	* _strtok - a re-implementation of
	* the strtok function.
	* converts input string to tokens
	* @str: parameter of type char *.
	* @delim: the delimiter
	* Return: char *.
	* description: checked
*/
char *_strtok(char *str, char *delim)
{
	static int _index, _len;
	int start, i;
	static char *buff;

	if (str)
	{
		free(buff), _index = 0, _len = _strlen(str);
		buff = malloc(sizeof(char) * _strlen(str) + 1);
		if (!buff)
			return (NULL);
		_memcpy(str, buff, _len), buff[_len] = '\0';
		for (i = _index; buff[i] && in_str(buff[i], delim); i++)
			buff[i] = '\0';
		start = i;
		for (; buff[i] && !in_str(buff[i], delim); i++)
			;
		for (; buff[i] && in_str(buff[i], delim); i++)
			buff[i] = '\0';
		_index += i;
		return (buff + start);
	}
	else
	{
		if (_index >= _len)
		{
			free(buff), buff = NULL;
			return (NULL);
		}
		start = _index;
		for (i = _index; buff[i] && !in_str(buff[i], delim); i++)
			_index++;
		for (; buff[i] && in_str(buff[i], delim); i++)
			_index++, buff[i] = '\0';
		return (buff + start);
	}
}

/**
 * com_tok - a modified version of the _strtok
 * it uses logical operator as delimiters
 * and only takes in a delimiter at a time
 * (as intended)
 * @str: the string to tokenize
 * @delim: the delimiter
 * Return: one token at a time
 * description: checked
 **/
char* com_tok(char* str, char* delim)
{
	static int _index, _len;
	int start, i, noc, acn, lb;
	static char *buff;

	if (str)
	{
		free(buff), _index = 0, i = _index, _len = _strlen(str);
		buff = malloc(sizeof(char) * _strlen(str) + 1);
		if (!buff)
			return (NULL);
		_memcpy(str, buff, _len), buff[_len] = '\0';
		noc = first_oc_of(buff + i, *delim);
		acn = adj_char_num(buff + i + noc, buff[i + noc], 0);
		if (noc >= 0 && acn != 2)
			start = i, lb = 1, i += (noc + acn), _index += (noc + acn);
		for (; buff[i] && in_str(buff[i], delim); i++)
			buff[i] = '\0';
		if (!lb)
			start = i;
		for (; buff[i] && !in_str(buff[i], delim); i++)
			;
		_index = i, determine_jump(&buff, delim, &_index, &i);
		for (; buff[i] && in_str(buff[i], delim); i++)
			buff[i] = '\0', _index++;
		return (buff + start);
	}
	else
	{
		if (_index >= _len)
		{
			free(buff), buff = NULL;
			return (NULL);
		}
		for (start = i = _index; buff[i] && !in_str(buff[i], delim); i++)
			_index++;
		determine_jump(&buff, delim, &_index, &i);
		for (; buff[i] && in_str(buff[i], delim); i++)
			_index++, buff[i] = '\0';
		return (buff + start);
	}
}

/**
  * _trim - a function that trims
  * @str: the string to trim
  * Return: the trimmed string
	* description: checked
 */
char *_trim(char *str)
{
	int pos_start = 0, i = 0, pos_end = strlen(str) - 1,
	stat = 0;
	char *sp_char = " \t", *res = NULL;

	if (!str || !str[0])
		return (NULL);
	while (str[i] != '\0')
	{
		if (!(in_str(str[i], sp_char)))
			break;
		if (stat == 0)
		{
			stat = 1;
			pos_start = i;
			while ((in_str(str[pos_start], sp_char)))
				pos_start++;
		}
		i++;
	}
	i = pos_end;

	for (; i >= 0 && in_str(str[i], sp_char); i--)
		;
	pos_end = i;

	res = (char *)malloc((pos_end - pos_start + 2) * sizeof(char));
	if (res == NULL)
		return (res);
	for (i = 0, stat = pos_start; stat <= pos_end; stat++)
		res[i++] = str[stat];
	res[pos_end - pos_start + 1] = '\0';

	return (res);
}

/**
 * is_print - a function
 * that checks if a character is printable
 * @c: the character parameter
 * Return: int
 * description: checked
 **/
int is_print(char c)
{
	return (c >= 33 && c < 127);
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
