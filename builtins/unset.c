/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:35:29 by ababdoul          #+#    #+#             */
/*   Updated: 2025/04/22 16:07:38 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int is_valid_env_key(const char *key)
{
    int i;

    if (!key || !*key || ft_isdigit(*key))
        return (0);

    i = 0;
    while (key[i])
    {
        if (!ft_isalnum(key[i]) && key[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

static void remove_env_node(t_env **env_list, t_env *to_remove)
{
    if (!env_list || !*env_list || !to_remove)
        return;

    // Update previous node's next pointer
    if (to_remove->prev)
        to_remove->prev->next = to_remove->next;
    else  // Removing head node
        *env_list = to_remove->next;

    // Update next node's prev pointer
    if (to_remove->next)
        to_remove->next->prev = to_remove->prev;

    // Free memory
    free(to_remove->value);
    free(to_remove);
}

int ft_unset(char **args, t_obj *obj)
{
    int i = 1;
    int ret = 0;
    size_t key_len;
    t_env *current;
    t_env *next;

    if (!args[1])
        return (0);
    current = obj->env;
    while (args[i])
    {
        if (!is_valid_env_key(args[i]))
        {
            ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
            ft_putstr_fd(args[i], STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            ret = 1;
            i++;
            continue;
        }
        key_len = ft_strlen(args[i]);
        current = obj->env;
        while (current)
        {
            next = current->next;  // Save next pointer before potential removal
            if (ft_strncmp(current->value, args[i], key_len) == 0 &&
                (current->value[key_len] == '=' || current->value[key_len] == '\0'))
            {
                remove_env_node(&obj->env, current);
            }
            current = next;
        }
        i++;
    }
    return (ret);
}
