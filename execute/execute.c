#include "../includes/minishell.h"


void	child_process_execution(t_obj *obj, char *path, t_cmd *cur_cmd, char **env)
{
    path = validate_and_get_path(cur_cmd->argv, env);
    if (path == NULL)
    {
        perror("command not found");
        exit(determine_exit_code(obj, 127));
    }
    execve(path, cur_cmd->argv, env);
    determine_exit_code(obj, 130);
    perror("execve err");
    free(path);
    exit(determine_exit_code(obj, 126));
}

void	child_process(t_obj *obj, t_cmd *cur_cmd, int fd_pipe[2], char **env)
{
    char *path;

    path = NULL;
    close(fd_pipe[0]);
    if (cur_cmd->next != NULL)
    {
        dup2_error(obj, dup2(fd_pipe[1], STDOUT_FILENO));
        close(fd_pipe[1]);
    }
    if (set_redirections(cur_cmd) == Q_ERROR)
		exit(determine_exit_code(obj, Q_ERROR));
    // if (cur_cmd->argv[0] && check_buildings(cur_cmd->argv))// to do
	// 	run_buildings(obj, cur_cmd->argv);// to do
    child_process_execution(obj, path, cur_cmd, env);
    // else
    // {
    // }
    exit(determine_exit_code(obj, 130));
}

void	parent_process(t_obj *obj, t_cmd *curr_cmd, int fd_pipe[2])
{
    close(fd_pipe[1]);
	if (curr_cmd->next == NULL)
		close(fd_pipe[0]);
	else
	{
		dup2_error(obj, dup2(fd_pipe[0], STDIN_FILENO));
		close(fd_pipe[0]);
	}
}

void	execution_loop(t_obj *obj, int fd_in, int fd_out, char **env)
{
    t_cmd   *cur_cmd;
    int     pid;
    int ft_pipe[2];

    cur_cmd = obj->cmd;
    pid = 0;
    obj->pid = malloc(sizeof(t_cmd) * count_cmds(obj));
    while (cur_cmd)
    {
        pipe_error(obj, pipe(ft_pipe));
        obj->pid[pid] = fork_error(obj, fork());
        if (obj->pid[pid] == 0)
        {
            close(fd_in);
            close(fd_out);
            child_process(obj, cur_cmd, ft_pipe, env);
        }
        else
        {
            parent_process(obj, cur_cmd, ft_pipe);
            cur_cmd = cur_cmd->next;
            pid++;
        }
    }
}

int	execute(t_obj *obj, char **env)
{
    int status;
    t_cmd *cur_cmd;
    int std_in;
    int std_out;

    std_in = dup_error(obj, dup(STDIN_FILENO));
    std_out = dup_error(obj, dup(STDOUT_FILENO));
    cur_cmd = obj->cmd;
    ft_heredoc(obj);
    // and you need the check_build function
    // if (cur_cmd && cur_cmd->argv[0] && check_build(cur_cmd->argv) && cur_cmd->next == NULL)
    // {

    // }
    if (cur_cmd && cur_cmd->argv[0])
    {
        execution_loop(obj, std_in, std_out, env);
        ft_wait_all(obj, &status);
    }
    dup2_error(obj, dup2(std_in, STDIN_FILENO));
    dup2_error(obj, dup2(std_out, STDOUT_FILENO));
    close_fds(std_in, std_out);
    return (130);
}