/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:03:28 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/23 14:49:55 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char str, int *pair_quote, int *single_quote)
{
	if (str == '"' && *pair_quote == 0 && *single_quote == 0)
	{
		(*pair_quote)++;
		return (1);
	}
	else if (str == '"' && *pair_quote == 1)
	{
		(*pair_quote)--;
		return (1);
	}
	if (str == '\''  && *single_quote == 0 && *pair_quote == 0)
	{
		(*single_quote)++;
		return (1);
	}
	else if (str == '\''  && *single_quote == 1)
	{
		(*single_quote)--;
		return (1);
	}
	return (0);
}

int	lenght_without_quotes(char *str)
{
	int count;
	int len;
	int flag[2];

	len = 0;
	count = 0;
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;
	while (str[count])
	{
		len -= check_quote(str[count], &flag[P_QUOTE], &flag[S_QUOTE]);
		len++;
		count++;
	}
	return(len);
}

char    *set_quotes(char *str)
{
	int		count;
	int 	count2;
	int		flag[2];
	char	*set_quotes; 
	
	count = 0;
	count2 = 0;
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;
	set_quotes =malloc(sizeof(char) * (lenght_without_quotes(str) + 1));
	while (str[count])
	{
		if (check_quote(str[count], &flag[P_QUOTE], &flag[S_QUOTE]))
			count++;
		else
		{
			set_quotes[count2] = str[count];
			count2++;
			count++;
		}
	}
	set_quotes[count2] = '\0';
	return(set_quotes);
}