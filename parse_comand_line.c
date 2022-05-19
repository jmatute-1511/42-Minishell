/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_comand_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:36:26 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/19 17:15:57 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int check_quotes(char *str)
{
	int count;
	int simple_quote;
	int pair_quote;

	pair_quote = 0;
	simple_quote = 0;
	count = 0;
	while (str[count] )
	{
		if (str[count] == '"'  && pair_quote == 0 && simple_quote == 0)
			pair_quote++;
		else if (str[count] == '"'  && pair_quote == 1)
			pair_quote--;
		if (str[count] == '\''  && simple_quote == 0 && pair_quote == 0)
			simple_quote++;
		else if (str[count] == '\''  && simple_quote == 1)
			simple_quote--;
		count++;
	}
	if (pair_quote != 0  || simple_quote != 0)
		return (1);
	return (0);
}

int check_is_spaces(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f' || c == '\r'  \
	|| c == '$')
		return (1);
	return (0);
}

int	move_along_iterator(char *str)
{
	int count;

	count = 0;;
	while(str[count]  )
	{
		if (check_is_spaces(str[count]))
			break;
		count++;
	}
	return (count);
}
