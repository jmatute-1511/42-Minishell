/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 12:14:18 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/04 14:02:56 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_chr(char c)
{
	if (c == ' ' || c == '$' || c == '\'' || c == '"')
		return (1);
	else if (ft_isalpha(c) == 0 && ft_isalnum(c) == 0)
		return (1);
	return (0);
}

int	ft_point_strstr(char *str)
{
	int	count_str;

	count_str = 0;
	while (str[count_str])
	{
		if (check_chr(str[count_str]))
			return (count_str);
		count_str++;
	}
	return (count_str);
}

void	check_quotes(char str, int *pair_quote, int *single_quote)
{
	if (str == '"' && *pair_quote == 0 && *single_quote == 0)
		(*pair_quote) += 1;
	else if (str == '"' && *pair_quote == 1)
		(*pair_quote) -= 1;
	if (str == '\'' && *single_quote == 0 && *pair_quote == 0)
		(*single_quote) += 1;
	else if (str == '\'' && *single_quote == 1)
		(*single_quote) -= 1;
}

int	comp_with_string(char chr, char *str)
{
	int	count;
	int	count2;

	count = 0;
	count2 = 0;
	while (str[count])
	{
		if (str[count] == chr)
			return (1);
		count++;
	}
	return (0);
}

char	*ft_strchrdup_quote(char *str, char *chr)
{
	int		count;
	char	*line;
	int		flag[2];

	count = 0;
	line = NULL;
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;
	while (str[count])
	{
		if (ft_strchr(chr, str[count]) != NULL && \
		flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0)
			break ;
		check_quotes(str[count], &flag[P_QUOTE], &flag[S_QUOTE]);
		count++;
	}
	if (count != 0)
		line = ft_strldup(str, count);
	return (line);
}
