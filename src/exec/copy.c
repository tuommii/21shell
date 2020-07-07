#include "shell.h"

char	**make_cmd(char *path, char *input)
{
	char	**cmd;

	if (!(cmd = (char **)malloc(sizeof(char *) * (2 + 1))))
		exit_error(MALLOC_ERROR, STR_MALLOC_ERR);
	cmd[0] = ft_strdup(path);
    cmd[1] = ft_strdup(input);
	cmd[2] = NULL;
	return (cmd);
}

int			mini_exec(char **args)
{
	int		status;

	if ((status = execve(args[0], args, g_sh.env)) == -1)
		exit_error(EXECVE_ERROR, STR_EXECVE_ERR);
	return (status);
}

int         pipe_right(int pfd[2])
{
    int     status;
    pid_t   child_pid;

	// ft_putendl("exec pipe right");
	status = 0;
	if ((child_pid = fork()) == -1)
		exit_error(FORK_ERR, STR_FORK_ERR);
	if (!child_pid)
	{
		// ft_putendl("exec pipe right pid 0");
		close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
		exit(mini_exec(make_cmd("pbcopy", NULL)));
	}
	else
	{
		// ft_putendl("exec pipe right else");
		close(pfd[1]);
		waitpid(child_pid, &status, 0);
	}
	return (status);
}

int         pipe_left(int pfd[2], char **args)
{
    int     status;
    pid_t   child_pid;

    if ((child_pid = fork()) == -1)
        exit_error(FORK_ERR, STR_FORK_ERR);
    else if (!child_pid)
    {
		// ft_putendl("exec pipe left no pid");
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		exit(mini_exec(args));        
    }
    else
    {
		// ft_putendl("exec pipe left else");
		status = pipe_right(pfd);
		close(pfd[0]);
		waitpid(child_pid, NULL, 0);        
    }
	return (status);
}

int         copy_to_clipboard(char *input)
{
    int     pfd[2];
    int		status;
    char    **args;

    // ft_putendl("pipe");
	if (pipe(pfd) == -1)
	{
		print_error(PIPE_ERR, NULL);
		return (EXEC_ERROR);
	}
    // ft_putendl("pipe left");
    args = make_cmd("/bin/echo", input);
    pipe_left(pfd, args);
    return(0);
}