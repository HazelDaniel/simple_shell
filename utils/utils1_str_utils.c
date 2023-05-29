#include "main.h"

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

char *com_tok(char *str, char *delim)
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
		return (_strddup(buff + start));
	}
	else
	{
		if (_index >= _len)
		{
			free(buff);
			return (NULL);
		}
		start = _index;
		for (i = _index; buff[i] && !in_str(buff[i], delim); i++)
			_index++;
		for (; buff[i] && in_str(buff[i], delim); i++)
			_index++, buff[i] = '\0';
		return (_strddup(buff + start));
	}
}
/**
  * _trim - a function that trims
  * @str: the string to trim
  * Return: the trimmed string
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
