#include "main.h"

/**
  * append_trash - appends a trash to the environment trash
  * @value: parameter of type char *.
  * @index: parameter of type int .
	* Description: checked
  * Return: void .
 */
void append_trash(char *value, int index)
{
	trashenv_t *new_trash = (trashenv_t *)malloc(sizeof(trashenv_t)), *current;

	if (!new_trash)
		return;
	new_trash->value = _strddup(value);
	new_trash->index = (int *)malloc(sizeof(int *));
	*(new_trash->index) = index;
	new_trash->next = NULL;

	if (!env_trash)
	{
		env_trash = new_trash;
	}
	else
	{
		current = env_trash;

		while (current && current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_trash;
	}
}

/**
  * clear_trash - clears the environment trash
	* @list: parameter of type trashenv_t *
  * Return: void .
	* Description: checked
 */
void clear_trash()
{
	trashenv_t *current = env_trash, *next = NULL;

	if (!current)
		return;
	while (current)
	{
		if (current->next == NULL)
		{
			_free_(current->value);
			_free_(current->index), _free_(current);
			env_trash = current;
			return;
		}
		next = current->next;
		_free_(current->value);
		_free_(current->index);
		_free_(current);
		current = next;
	}
}

/**
  * remove_trash - removes an entry from the environment trash
  * @value: parameter of type char *.
  * @list: parameter of type trashenv_t *
	* Description: checked
  * Return: void .
 */
void remove_trash(char *value)
{
	trashenv_t *current = env_trash, *prev = NULL;

	if (!current)
		return;
	while (current && (_strcmp(current->value, value)))
	{
		prev = current;
		current = current->next;
	}
	if (current)
	{
		if (!prev)
			env_trash = current->next;
		else
			prev->next = current->next;
		_free_(current->value);
		_free_(current->index);
		_free_(current);
	}
}

/**
  * get_trash - retrieves a trash from the
	* environment trash
  * @value: parameter of type char *.
  * @list: parameter of type trashenv_t *
  * Return: trashenv_t *
	* Description: checked
 */
trashenv_t *get_trash(trashenv_t *list, char *value)
{
	trashenv_t *current = list, *prev = NULL;

	while (current && (_strcmp(current->value, value)))
	{
		prev = current;
		current = current->next;
	}

	return (current);
}

/**
  * pop_trash - pops an environment trash
  * Return: trashenv_t *
	* Description: checked
 */
trashenv_t *pop_trash()
{
	trashenv_t *current = env_trash;

	if (!env_trash)
		return (NULL);
	env_trash = env_trash->next;
	return (current);
}

