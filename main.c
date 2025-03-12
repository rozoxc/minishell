/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 03:58:40 by ababdoul          #+#    #+#             */
/*   Updated: 2025/03/12 04:07:28 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int main()
{
   char *line;
   size_t line_size;
   size_t read;

   line = NULL;
   read = 0;
   while (1)
   {
    printf("sh$ ");
    read = getline(&line, &line_size, stdin);
    if (read == -1)
        break;
        printf("you enter %s\n", line);
    }
    return (0);
}