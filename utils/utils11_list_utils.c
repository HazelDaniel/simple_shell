#include "main.h"

/**
 * linkpath - creates a linked list for path directories
 * @path: string of path value
 * Return: pointer to the created linked list
 */
void linkpath(char *path)
{
	pathdir_t *head = NULL;
	char *token;
	char *cpath = _strddup(path);

	token = _strtok(cpath, ":");
	while (token)
	{
		append_path(token);
		token = _strtok(NULL, ":");
	}
	empty_state_buff(":");
	_free_(cpath);
}

/**
 * append_path - appends a directory to the path environment
 * @value: the directory string
 * Return: void
 */
void append_path(char *value)
{ pathdir_t *new_path = (pathdir_t *)malloc(sizeof(pathdir_t)), *current;
	char *cpy = _strddup(value), *strip_cpy = rm_tr_slash(cpy);

	if (!new_path)
		return;
	new_path->dir = strip_cpy;
	new_path->next = NULL;

	if (!path_list)
	{
		path_list = new_path;
	}
	else
	{
		current = path_list;
		while (current && current->next != NULL)
			current = current->next;
		current->next = new_path;
	}
	_free_(cpy);
}

/**
 * print_path - prints the path variable
 * Return: void
 */
void print_path(void)
{
	pathdir_t *current = path_list;

	if (!current)
	{
		puts("(nil)");
	}
	while (current)
	{
		printf("current directory:%s\n", current->dir);
		current = current->next;
	}
}
/**
 * free_path - frees the path variable
 * Return: void
 */
void free_path(void)
{
	pathdir_t *current = path_list, *next;

	if (!current)
		return;

	while (current)
	{
		next = current->next;
		_free_(current->dir);
		_free_(current);
		current = next;
	}

}

/**
  * print_trash - prints the environment trash
	* @list:  a parameter of type trashenv_t *
  * Return: void
	* Description: checked
 */
void print_trash()
{
	trashenv_t *current = env_trash;

	if (!env_trash)
	{
		puts("(nil)");
		return;
	}
	while (current)
	{
		printf("current trash:%s\n", current->value);
		current = current->next;
	}
}
