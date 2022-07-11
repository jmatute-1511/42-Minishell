/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bremesar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:34:04 by bremesar          #+#    #+#             */
/*   Updated: 2022/07/11 12:34:06 by bremesar         ###   ########.fr       */
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
