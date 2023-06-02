#include "main.h"

/**
  * _freenv - a function that
	* frees the environment
  * Return: void
 */
void _freenv(void)
{
	free_str_arr(new_environ, 1);
	new_environ = NULL;
}

/**
  * clear_comms - a function that clears
	* all commands
	* @list: a parameter of type comm_list_t
  * Return: void .
 */
void clear_comms(comm_list_t *list)
{
	comm_list_t current = *list, next = NULL;

	if (!current)
		return;
	while (current)
	{
		if (current->next == NULL)
		{
			_free_(current->status);
			_free_(current->command);
			_free_(current->separator);
			_free_(current);
			return;
		}
		next = current->next;
		if (current->is_linked)
			clear_comms(&(current->list));
		_free_(current->status);
		_free_(current->command);
		_free_(current->separator);
		_free_(current);
		current = next;
	}
}

/**
  * free_commands - a function that frees
	* all commands
  * Return: void .
 */
void free_commands(void)
{
	int i = 0, j = 0;

	if (!commands)
		return;

	for (i = 0; commands[i]; i++)
	{
		clear_comms(&(commands[i]));
	}
	_free_(commands);
}

/**
  * remove_command - a function that removes
	* a command from a command flow
	* @list: parameter of type comm_t **
	* @value: the id of the command
  * Return: void .
 */
void remove_command(comm_t **list, int value)
{
	comm_t *current = *list, *prev = NULL;

	if (!current)
		return;
	while (current && (current->id != value))
	{
		prev = current;
		current = current->next;
	}
	if (current)
	{
		if (!prev)
			*list = current->next;
		else
			prev->next = current->next;
		_free_(current->command);
		_free_(current->status);
		_free_(current);
	}
}
