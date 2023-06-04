#include "main.h"

/**
 * error_env - Creates an error message for env errors.
 * @args: An array of arguments passed to the command.
 * Return: The error string.
 */
char *error_env(char **args)
{
	char *error, *hist_str;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	args--;

	error = _strvcat(name, ": ", hist_str,
	": ", args[0], ": Unable to add/remove from environment\n", NULL);

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

	error = _strvcat("alias:", args[0], " not found\n", NULL);

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

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	error = _strvcat(name, ": ", hist_str,
		" exit: Illegal number: ", args[0], "\n", NULL);

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
	char *error = NULL, *hist_str, *tmp;

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

	if (args[0][0] == '-')
		tmp = ": cd: Illegal option ";
	else
		tmp = ": cd: can't cd to ";
	error = _strvcat(name, ": ", hist_str, tmp, args[0], "\n", NULL);

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

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	error = _strvcat(name, ": ", hist_str, ": Syntax error: \"",
		args[0], "\" unexpected\n", NULL);

	_free_(hist_str);

	return (error);
}
