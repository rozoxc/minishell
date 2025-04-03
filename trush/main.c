/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 03:58:40 by ababdoul          #+#    #+#             */
/*   Updated: 2025/03/18 06:15:28 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main()
{
    char *line;
    // atexit(f);
    while (1)
    {
        line = readline("$minishell > ");
        if (line == NULL)
            printf("Error\n");
        else if (strcmp(line, "exit") == 0)
            break;
        if (*line)
            add_history(line);
        printf("you enter %s\n", line);

        free(line);
    }
    return (0);
}