/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:43:53 by ababdoul          #+#    #+#             */
/*   Updated: 2025/04/22 13:56:32 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void update_env_var(const char *key, const char *value)
// {
//     t_env *env = g_env;
//     while (env)
//     {
//         if (strcmp(env->value, key) == 0) {
//             free(env->value);
//             env->value = strdup(value);
//             return;
//         }
//         env = env->next;
//     }
//     // If not found, add a new entry
//     t_env *new_env = malloc(sizeof(t_env));
//     new_env->value = strdup(key);
//     new_env->value = strdup(value);
//     new_env->next = g_env;
//     g_env = new_env;
// }
int ft_cd(char **args)
{
    char old_pwd[PATH_MAX];
    char new_pwd[PATH_MAX];

    if (!args[1])
    {
        printf("missing argument !!\n");
        return (1);
    }
    if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
    {
        perror("getcwd");
        return (1);
    }
    if (chdir(args[1]) != 0)
    {
        perror("cd");
        return (1);
    }
    if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
        return(perror("getcwd"), 1);
    // update_env_var("OLDPWD", old_pwd);
    // update_env_var("PWD", new_pwd);
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

