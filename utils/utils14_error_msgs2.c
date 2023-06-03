#include "main.h"


/**
 * error_126 - Creates an error message for permission denied failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_126(char **args)
{
	char *error, *hist_str;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	error = _strvcat(name, ": ", hist_str, ": ", args[0], ": Permission denied\n", NULL);

	_free_(hist_str);
	return (error);
}

/**
 * error_127 - Creates an error message for command not found failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_127(char **args)
{
	char *error, *hist_str;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);


	error = _strvcat(name, ": ", hist_str, ": ", args[0], ": not found\n", NULL);

	_free_(hist_str);
	return (error);
}
