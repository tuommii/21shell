#include "shell.h"

char	**make_cmd(char *input)
{
	char	**cmd;

	if (!(cmd = (char **)malloc(sizeof(char *) * (2 + 1))))
		exit_error(MALLOC_ERROR, STR_MALLOC_ERR);
	cmd[0] = ft_strdup("/bin/echo");
    cmd[1] = ft_strdup(input);
	cmd[2] = NULL;
	return (cmd);
}

int         pipe_writer(int pfd[2], char **args)
{
    int     status;
    pid_t   child_pid;

    child_pid = fork();
    if (child_pid == -1)
        exit_error(FORK_ERR, STR_FORK_ERR);
    dup2(pfd[1], STDOUT_FILENO);
    close(pfd[0]);
    // close(pfd[1]);
    // array_debug(args);
	if ((status = execve("/bin/echo", args, g_sh.env)) == -1)
		exit_error(EXECVE_ERROR, STR_EXECVE_ERR);
	return (0);   
}

int         copy_to_clipboard(char *input)
{
    int pfd[2];
    char **args;


	if (pipe(pfd) == -1)
	{
		print_error(PIPE_ERR, NULL);
		return (EXEC_ERROR);
	}

    args = make_cmd(input);
    pipe_writer(pfd, args);
    // pipe_reader(pfd);
    // pid_right = fork()
    return(0);
}