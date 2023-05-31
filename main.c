#include "utils/main.h"

comm_list_t *commands = NULL;
int comms_index = -1;
char **new_environ = NULL, *name, *callpwd;
trashenv_t *env_trash = NULL;
pathdir_t *path_list = NULL;
alias_t *aliases = NULL;
var_t *variables = NULL;
int hist;
char *prompts[10] =
{"_$ ", " ___(($USER@$hostname)-[$PWD]\n|___: ", "$"}, *prompt;

int main (int argc, char **argv, char **envp)
{
	(void)envp;
	char *token, *str = "&&&i &what is && the matter &&& if ?& hello world && how", *delim = "&";

	token = com_tok(str, delim);
	while (token && token[0])
	{
		printf("token is :%s:\n", token);
		token = com_tok(NULL, delim);
	}

	return (0);
}
