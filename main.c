#include "utils/main.h"

/* GLOBAL DECLARATIONS */
comm_list_t *commands = NULL;
int comms_index = -1;
char **new_environ = NULL, *name, *callpwd;
trashenv_t *env_trash = NULL;
pathdir_t *path_list = NULL;
alias_t *aliases = NULL;
var_t *variables = NULL;
int hist;
char *prompts[10] =
{"_$ ", " ___($USER@$hostname)-[$PWD]\n|___: ", "$"}, *prompt;

/**
 * handle_signal - the signal handler for CTRL-C
 * @sig: the signal in number
 * Return: nothing
 **/
void handle_signal(int sig)
{
	char *sig_str = _itoa(sig);

	(void)sig;
	if (isatty(STDIN_FILENO))
	{
		signal(SIGINT, handle_signal);
		fflush(stdin);
		write(STDIN_FILENO, "\n", 1);
		write(STDIN_FILENO, prompt, _strlen(prompt));
	}
}


/**
 * main - the entry point into the program
 * @argc: the argument count
 * @argv: the argument vector
 * @envp: the environment pointer
 * Return: int
 **/
int main(int argc, char *argv[], char *envp[])
{
	char *str, *token, *buff;
	int i;

	i = _setvar("?=2");
	puts("working");
	i = _setvar("?=0");
	str = _getvar("$?");

	printf("the string is :%s:\t and the index was :%d:\n", str, i);

	free(str);
	cleanup();

	return (0);
}
