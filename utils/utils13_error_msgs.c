#include "main.h"

/**
 * error_env - Creates an error message for env errors.
 * @args: An array of arguments passed to the command.
 * Return: The error string.
 */
char *error_env(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	args--;
	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 45;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		_free_(hist_str);
		return (NULL);
	}

	_memcpy(name, error, _strlen(name));
	_strncat(error, ": ", 2);
	_strncat(error, hist_str, _strlen(hist_str));
	_strncat(error, ": ", 2);
	_strncat(error, args[0], _strlen(args[0]));
	_strncat(error, ": Unable to add/remove from environment\n", 40);

	_free_(hist_str);
	return (error);
}

/**
 * error_1 - Creates an error message for alias errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_1(char **args)
{
	char *error;
	int len;

	len = _strlen(name) + _strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	_memcpy("alias: ", error, _strlen("alias: "));
	_strncat(error, args[0], _strlen(args[0]));
	_strncat(error, " not found\n", 12);

	return (error);
}

/**
 * error_2_exit - Creates an error message for exit errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_exit(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		_free_(hist_str);
		return (NULL);
	}

	_memcpy(name, error, _strlen(name));
	_strncat(error, ": ", 2);
	_strncat(error, hist_str, _strlen(hist_str));
	_strncat(error, ": exit: Illegal number: ", 25);
	_strncat(error, args[0], _strlen(args[0]));
	_strncat(error, "\n", 1);

	_free_(hist_str);
	return (error);
}

/**
 * error_2_cd - Creates an error message for cd errors.
 * @args: An array of arguments passed to the command.
 * Return: The error string.
 */
char *error_2_cd(char **args)
{
	char *error = NULL, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);
	if (!args)
	{
		puts("no argument passed!");
		return (NULL);
	}

	if (args[0][0] == '-')
		args[0][2] = '\0';
	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		_free_(hist_str);
		return (NULL);
	}

	_memcpy(name, error, _strlen(name));
	_strncat(error, ": ", 2);
	_strncat(error, hist_str, _strlen(hist_str));
	if (args[0][0] == '-')
		_strncat(error, ": cd: Illegal option ", 22);
	else
		_strncat(error, ": cd: can't cd to ", 19);
	_strncat(error, args[0], _strlen(args[0]));
	_strncat(error, "\n", 1);

	_free_(hist_str);
	return (error);
}

/**
 * error_2_syntax - Creates an error message for syntax errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_syntax(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		_free_(hist_str);
		return (NULL);
	}

	_memcpy(name, error, _strlen(name));
	_strncat(error, ": ", 2);
	_strncat(error, hist_str, _strlen(hist_str));
	_strncat(error, ": Syntax error: \"", 18);
	_strncat(error, args[0], _strlen(args[0]));
	_strncat(error, "\" unexpected\n", 14);

	_free_(hist_str);

	return (error);
}
