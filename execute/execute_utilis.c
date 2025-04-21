#include "../includes/minishell.h"

void	close_fds(int fd1, int fd2)
{
	if (fd1 >= 0)
		close(fd1);
	if (fd2 >= 0)
		close(fd2);
}


int count_cmds(t_obj *obj)
{
	t_cmd *cmd_temp;
	int count;

	count = 0;
	cmd_temp = obj->cmd;
	while (cmd_temp)
	{
	count++;
	cmd_temp = cmd_temp->next;
	}
	return (count);
}

void ft_wait_all(t_obj *obj)
{
    int status;
    int i = 0;
    int cmd_count = count_cmds(obj);

    while (i < cmd_count)
    {
        pid_t pid = waitpid(obj->pid[i], &status, 0);
        if (pid == -1)
        {
            perror("waitpid failed");
            obj->exit_code = 1; // Assign a generic error code
        }
        else
        {
            if (WIFEXITED(status))
                obj->exit_code = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                obj->exit_code = 128 + WTERMSIG(status);
            else
                obj->exit_code = 1; // Fallback for other cases
        }
        i++;
    }
    free(obj->pid);
}