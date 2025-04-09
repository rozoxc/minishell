#include "../includes/minishell.h"

char	*free_paths_return(char **paths, char *return_value)
{
	int	i;

	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (return_value);
}

char	*find_path(char *command, char **envp)
{
	int		i;
	char	*path;
	char	*path_part;
	char	**paths;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path_part = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path_part, command);
		free(path_part);
		if (access(path, X_OK) == 0)
			return (free_paths_return(paths, path));
		free(path);
		i++;
	}
	return (free_paths_return(paths, 0));
}

char	*validate_and_get_path(char **command, char **envp)
{
	char	*path;

	if (command[0] == NULL)
		path = find_path(command[0], envp);
	else if (command[0][0] == '.' && command[0][1] == '/' )
		path = ft_strdup(command[0]);
	else if (command[0][0] == '/')
		path = ft_strdup(command[0]);
	else
		path = find_path(command[0], envp);
	return (path);
}