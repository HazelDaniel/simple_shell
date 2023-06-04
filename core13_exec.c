#include "utils/main.h"

/**
 * execute - a function that executes a command
 * @comm_str: the command string to execute
 * Return: int
 **/
int execute(char *comm_str)
{
	char **args, *command = _strddup(comm_str);
	int (*f)(char **list), ret_num = 0, status;
	pid_t child_pid;

	args = _splitstr(command, "\n\r\a\t ");
	format_args(args);
	if (args && args[0])
	{
		_free_(command), command = args[0];
		f = get_builtin(command);
		if (f)
		{
			ret_num = f(args + 1);
			if (create_ex_stat(ret_num))
				return (1);
		}
		else
		{
			if (command && command[0] != '/' && command[0] != '.')
			{
				command = _trace(command);
				if (!command)
					command = args[0];
				else
					_free_(args[0]), args[0] = command;
			}
			if (!command || (access(command, F_OK) == -1))
			{
				if (errno == EACCES)
					ret_num = (create_error(args, 126)), create_ex_stat(ret_num);
				else
					ret_num = (create_error(args, 127)), create_ex_stat(ret_num);
			}
			else
			{
				child_pid = fork();
				if (child_pid == -1)
				{
					free_str_arr(args, 1);
					perror("Error forking child:");
					return (1);
				}
				if (child_pid == 0)
				{
					execve(command, args, new_environ);
					if (errno == EACCES)
						ret_num = (create_error(args, 126));
					if (create_ex_stat(ret_num))
						return (1);
					cleanup(), _exit(ret_num);
				}
				else
				{
					wait(&status);
					ret_num = WEXITSTATUS(status);
					if (create_ex_stat(status))
						return (1);
				}
				if (create_ex_stat(0))
					return (1);
			}
		}
	}
	free_str_arr(args, 1);

	if (create_ex_stat(ret_num))
		return (1);
	return (ret_num);
}

/**
 * create_ex_stat - a function that
 * sets the exit status of a process
 * to a shell variable $?
 * @status: a parameter of type int
 * Return: int
 * description: checkpoint
 **/
int create_ex_stat(int status)
{
	char *tmp, *res;

	tmp = _itoa(status);
	if (!tmp)
		return (1);
	res = _strvcat("?=", tmp, NULL);
	if (!_setvar(res))
	{
		_free_(tmp), _free_(res);
		return (1);
	}
	_free_(tmp), _free_(res);

	return (0);
}

/**
 * create_pid - a function that
 * sets the pid of a process
 * to a shell variable $$
 * @pid: a parameter of type int
 * Return: int
 **/
int create_pid(int pid)
{
	char *tmp, *res;

	tmp = _itoa(pid);
	if (!tmp)
		return (1);
	res = malloc(_strlen(tmp) + 3);
	if (!res)
	{
		_free_(tmp);
		return (1);
	}
	res[0] = '$', res[1] = '=';
	_memcpy(tmp, res + 2, _strlen(tmp));
	if (!_setvar(res))
	{
		_free_(tmp), _free_(res);
		return (1);
	}
	_free_(tmp), _free_(res);

	return (0);
}
