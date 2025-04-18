/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:16:32 by ababdoul          #+#    #+#             */
/*   Updated: 2025/04/14 18:03:43 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_pwd()
{
    char path[200];
    
    if (getcwd(path, sizeof(path)) == NULL)
    {
        perror("getwc!!");
        return (FAILURE);
    }
    printf("%s\n", path);
    return (SUCCESS);
}
// int main()
// {
//     ft_pwd();
// }