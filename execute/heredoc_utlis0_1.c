/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utlis0_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:45:03 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/17 15:15:36 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*remove_all_quotes(const char *input)
{
	char	*result;
	int		pos;
	int		i;
	int		len;

	if (!input || !*input)
		return (strdup(""));
	len = strlen(input);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	pos = 0;
	i = 0;
	while (i < len)
	{
		if (input[i] == '\'')
			handle_single_quote(input, &i, result, &pos);
		else if (input[i] == '"')
			handle_double_quote(input, &i, result, &pos);
		else
			result[pos++] = input[i];
		i++;
	}
	result[pos] = '\0';
	return (result);
}

char	*ft_expand(t_obj *obj, char *str)
{
	char	**argv;
	int		i;

	i = 0;
	if (str == NULL || ft_strcmp(str, "") == 0)
		return (ft_strdup(""));
	argv = ft_split(str, ' ');
	free(str);
	str = NULL;
	while (argv[i])
	{
		if (ft_strrchr(argv[i], '$'))
		{
			str = ft_strjoin2(str, get_value(obj, argv[i] + 1), 2);
			free(argv[i]);
		}
		else
			str = ft_strjoin2(str, argv[i], 2);
		i++;
	}
	free(argv);
	return (str);
}
