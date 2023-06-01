#include "utils/main.h"

/**
 * getall_env - a function that prints
 * all environment variables
 * Return: int
 **/
int getall_env(void)
{
	int i = 0;

	if (!new_environ)
		return (-1);
	for (; new_environ[i]; i++)
		printf("%s\n", new_environ[i]);
	return (0);
}

/**
  * _getenv - a function that gets a variable environment
	* equivalent of a string
  * @input: parameter of type char *.
  * Return: char *.
 */
char *_getenv(char *input)
{
	int i = 0;
	char *token, *cp_buffer = NULL, *tok_cpy;

	if (!new_environ)
		return (NULL);
	for (; new_environ[i]; i++)
	{
		token = _strtok(new_environ[i], "=");
		if (!_strcmp(token, input))
		{
			token = _strtok(NULL, "=");
			tok_cpy = _strddup(token);
			empty_state_buff("=");
			return (tok_cpy);
		}
		empty_state_buff("=");
	}
	return (NULL);
}

/**
  * _setenv - a function that sets
	* a variable environment
  * @input1: parameter of type char *.
  * @input2: parameter of type char *.
  * Return: int .
 */
int _setenv(char *input1, char *input2)
{
	int i = 0, len1 = _strlen(input1), len2 = _strlen(input2),
	index = -1, p_len = _al_len_(new_environ), l_word;
	char *new_val = NULL, **tmp_env = new_environ, *val_equiv;
	trashenv_t *trash_equiv;

	new_val = malloc((len1 + len2 + 2));
	if (!new_val)
		return (-1);
	_memcpy(input1, new_val, len1), new_val[len1] = '=';
	_memcpy(input2, new_val + len1 + 1, len2);
	new_val[len1 + len2 + 1] = '\0';
	for (i = 0; new_environ[i]; i++)
	{
		l_word = last_spn_oc(is_word, new_environ[i]);
		val_equiv = _strddup(new_environ[i]), val_equiv[l_word + 1] = '\0';
		if (!_strcmp(input1, val_equiv))
		{
			free(new_environ[i]), free(val_equiv), val_equiv = NULL;
			new_environ[i] = NULL, new_environ[i] = new_val;
			return (0);
		}
		free(val_equiv), val_equiv = NULL;
	}
	trash_equiv = pop_trash();
	if (trash_equiv)
	{
		free(new_environ[*(trash_equiv->index)]);
		new_environ[*(trash_equiv->index)] = NULL;
		new_environ[*(trash_equiv->index)] = new_val;
		free(trash_equiv->index), free(trash_equiv->value);
		free(trash_equiv), trash_equiv = NULL;
		return (0);
	}
	new_environ = (char **)_realloc_ptr(new_environ, p_len,
		p_len + sizeof(char *));
	if (!new_environ)
		return (-1);
	new_environ[i] = new_val, new_environ[i + 1] = NULL;
	return (0);
}

/**
  * _copyenv - a function makes a copy
	* of the parent process's environment
  * Return: void
 */
void _copyenv(void)
{
	int count, i;

	free_str_arr(new_environ, 1);
	new_environ = NULL;

	count = _len_p((void **)environ);
	new_environ = malloc((count + 1) * sizeof(char *));
	if (!new_environ)
		return;
	_memcpy_ptr((void **)environ, (void **)new_environ, count);
}

/**
  * _unsetenv - a function that unsets
	* an environment variable
  * @value: parameter of type char *.
  * Return: int .
 */
int _unsetenv(char *value)
{
	int count, i;

	for (i = 0; new_environ[i]; i++)
	{
		if (is_start_str(value, new_environ[i]))
		{
			free(new_environ[i]);
			new_environ[i] = _strddup("|=|");
			append_trash(_strddup(value), i);
			break;
		}
	}
	if (new_environ[i])
		return (0);
	else
		return (-1);
}
