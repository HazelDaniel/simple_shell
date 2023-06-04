#include "utils/main.h"

static int compare_and_sub(var_t **current_ptr, var_t **new_ptr,
	char **input_ptr, char **cpy_ptr, char **key_ptr);
char *eval_n_expand(char **str_p);

/**
 * resize_s_arr -a function that expands a string array
 * @sarr_ptr: the address of the string array
 * @count: the length gained
 * Return: void
 **/
static void resize_s_arr(char ***sarr_ptr, int count)
{
	if (count >= 200)
		*sarr_ptr = (char **)_realloc_ptr(*sarr_ptr,
		_al_len_(*sarr_ptr), _al_len_(*sarr_ptr) + (2 * sizeof(char *)));
}
/**
 * _getall_vars - a function that retrieves
 * all the environment variables
 * Return: void
 **/
void _getall_vars(void)
{
	var_t *current = variables;

	if (!current)
		puts("(nil)");

	while (current)
	{
		printf("%s\n", current->value);
		current = current->next;
	}
}

/**
 * _getvar - a function that retrieves
 * a shell variable
 * @input: the input string
 * Return: char *
 **/
char *_getvar(char *input)
{
	char *token, *cp_buffer = NULL, *tok_cpy = NULL;
	var_t *current = variables;

	if (!current || !input || !is_start_str("$", input))
		return (NULL);
	while (current)
	{
		if (_strlen(input) == 1)
		{
			empty_state_buff("=");
			return (_strddup(input));
		}
		if (is_start_str(input + 1, current->value))
		{
			cp_buffer = _strddup(current->value);
			(void)_strtok(cp_buffer, "=");
			token = _strtok(NULL, "=");
			tok_cpy = _strddup(token);
			empty_state_buff("=");
			_free_(cp_buffer);
			return (tok_cpy);
		}
		current = current->next;
	}
	empty_state_buff("=");

	return (NULL);
}

/**
 * _setvar - a function that sets
 * a shell variable
 * @input: the input string
 * Return: int
 **/
int _setvar(char *input)
{
	var_t *current = variables, *new_var;
	char *cpy = NULL, *key = NULL;

	if (is_start_str("$", input) && !(is_start_str("$=", input)) &&
		!(is_start_str("?=", input)))
		return (0);

	new_var = (var_t *)malloc(sizeof(var_t));
	if (!new_var)
		return (0);
	new_var->value = _strddup(input), new_var->next = NULL;
	if (!variables)
	{
		variables = new_var;
		return (1);
	}
	cpy = _strddup(input), key = _strddup(_strtok(cpy, "="));
	empty_state_buff("="), current = variables;
	if (!current->next)
	{
		if (compare_and_sub(&current, &new_var, &input, &cpy, &key))
			return (1);
		current->next = new_var;
		return (1);
	}
	while (current && current->next)
	{
		if (compare_and_sub(&current, &new_var, &input, &cpy, &key))
			return (1);
		current = current->next;
	}
	if (compare_and_sub(&current, &new_var, &input, &cpy, &key))
		return (1);
	current->next = new_var;
	_free_(cpy), _free_(key);

	return (1);
}

/**
  * compare_and_sub - a utility function
	* for checking the existence of an alias
	* in the alias table
  * @current_ptr: parameter of type alias_t **
  * @new_ptr: parameter of type alias_t **
  * @input_ptr: parameter of type char **
  * @cpy_ptr: parameter of type char **
  * @key_ptr: parameter of type char **
  * Return: int
 */
static int compare_and_sub(var_t **current_ptr, var_t **new_ptr,
	char **input_ptr, char **cpy_ptr, char **key_ptr)
{
	if (!_strcmp(((*current_ptr)->value), *input_ptr))
	{
		_free_((*new_ptr)->value), _free_(*cpy_ptr), _free_(*new_ptr),
		_free_(*key_ptr);
		return (1);
	}
	else if (is_start_str(*key_ptr, (*current_ptr)->value))
	{
		_free_((*new_ptr)->value), _free_((*current_ptr)->value),
		_free_(*cpy_ptr), _free_(*key_ptr), _free_(*new_ptr);
		(*current_ptr)->value = _strddup(*input_ptr);
		return (1);
	}

	return (0);
}

/**
  * free_vars - a function that frees
	* the shell variables
  * Return: void
 */
void free_vars(void)
{
	var_t **current = &variables, *next = NULL;

	if (!*current)
		return;
	while (*current)
	{
		next = (*current)->next;
		_free_((*current)->value);
		_free_(*current);
		*current = next;
	}
	*current = NULL;
}

/**
  * lookup_var - a function that does
	* a lookup of any variable in both the shell
	* and the environment
  * @input: parameter of type char *.
  * Return: char *.
 */
char *lookup_var(char *input)
{
	char *buff = NULL;

	if (!is_start_str("$", input))
		return (NULL);

	buff = _getvar(input);
	if (!buff)
		buff = _getenv(input + 1);

	return (buff);
}

/**
  * var_replace - a function that does
	* a variable expansion on input strings
  * @str: the input string
  * Return: char *.
	* description: checked
 */
char *var_replace(char *str)
{
	int count = 0, s_ind, w_ind, i;
	char *sub_str = str, *tmp_sub, *sub_val, **s_arr = NULL, *res;

	s_arr = malloc(201 * sizeof(char *));
	if (!str)
		return (str);
	while (*sub_str && sub_str < str + _strlen(str))
	{
		if (*sub_str == '$')
		{
			w_ind = 1 + last_spn_oc(is_word, sub_str + 1);
			if (w_ind == 0)
			{
				tmp_sub = malloc(3 * sizeof(char));
				if (!tmp_sub)
					return (NULL);
				tmp_sub[0] = '$', tmp_sub[1] = sub_str[1], tmp_sub[2] = '\0';
				sub_val = lookup_var(tmp_sub);
				if (!sub_val)
					s_arr[count++] = _strddup("$"), sub_str++, _free_(tmp_sub);
				else
					s_arr[count++] = sub_val, sub_str += 2, _free_(tmp_sub);
				continue;
			}
			tmp_sub = malloc((w_ind) + 1 + 1);
			if (!tmp_sub)
				return (NULL);
			_memcpy(sub_str, tmp_sub, w_ind + 1), sub_val = lookup_var(tmp_sub);
			s_arr[count++] = sub_val ? sub_val : tmp_sub;
			if (sub_val)
				_free_(tmp_sub);
			resize_s_arr(&s_arr, count), sub_str += w_ind + 1;
		}
		else
		{
			tmp_sub = _strddup(sub_str), s_ind = 1 + first_oc(is_n_var, sub_str);
			if (s_ind > (int)_strlen(str))
				s_ind = _strlen(str);
			tmp_sub[s_ind] = '\0', s_arr[count++] = tmp_sub;
			resize_s_arr(&s_arr, count), sub_str += s_ind;
		}
	}
	for (i = 0; i < count; i++)
		;
	s_arr[i] = NULL, res = join_list(s_arr), free_str_arr(s_arr, 1);
	return (res);
}
