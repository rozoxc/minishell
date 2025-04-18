/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:43:53 by ababdoul          #+#    #+#             */
/*   Updated: 2025/04/16 12:17:47 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
extern char **environ;  // Access environment variables

void update_env_var(const char *key, const char *value)
{
    int i = 0;
    char *env_entry;
    char *new_env_entry;

    // Search for existing env var (key=)
    while (environ[i])
    {
        env_entry = environ[i];
        if (strncmp(env_entry, key, strlen(key)) == 0 && env_entry[strlen(key)] == '=')
        {
            // Found the key, now update its value
            new_env_entry = malloc(strlen(key) + strlen(value) + 2); // For key=value\0
            if (!new_env_entry)
            {
                perror("malloc");
                exit(1);
            }
            sprintf(new_env_entry, "%s=%s", key, value);
            environ[i] = new_env_entry; // Update the env variable
            return;
        }
        i++;
    }

    // If not found, add the new key=value entry
    environ[i] = malloc(strlen(key) + strlen(value) + 2);
    if (!environ[i])
    {
        perror("malloc");
        exit(1);
    }
    sprintf(environ[i], "%s=%s", key, value);
    environ[i + 1] = NULL;  // Ensure null-termination
}

int ft_cd(char **args)
{
    char old_pwd[1024];
    char new_pwd[1024];

    // Step 1: Check if argument exists
    if (!args[1])
    {
        write(2, "cd: missing argument\n", 22);
        return (1);
    }

    // Step 2: Save old PWD
    if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
    {
        perror("getcwd");
        return (1);
    }

    // Step 3: Try to change directory
    if (chdir(args[1]) != 0)
    {
        perror("cd");
        return (1);
    }

    // Step 4: Get the new PWD
    if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
    {
        perror("getcwd");
        return (1);
    }

    // Step 5: Update the environment variables
    update_env_var("OLDPWD", old_pwd);
    update_env_var("PWD", new_pwd);

    return (0);
}

// int main()
// {
//     char *args[] = {"cd", "/tmp", NULL};  // Test cd to /tmp
//     char *args_invalid[] = {"cd", "nonexistent", NULL};  // Test invalid path

//     printf("Testing ft_cd with valid path (cd /tmp):\n");
//     printf("Before cd:\n");
//     char cwd[1024];
//     if (getcwd(cwd, sizeof(cwd)) != NULL)
//         printf("Current directory: %s\n", cwd);

//     ft_cd(args);  // Call ft_cd with valid path

//     printf("After cd:\n");
//     if (getcwd(cwd, sizeof(cwd)) != NULL)
//         printf("Current directory: %s\n", cwd);

//     printf("\nTesting ft_cd with invalid path (cd nonexistent):\n");
//     ft_cd(args_invalid);  // Call ft_cd with invalid path
//     return 0;
// }

