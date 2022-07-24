/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boleans_first_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:57:03 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/24 19:32:29 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	bolean_without_arg(char *hdoc, int *count, int *signal)
{
	while (hdoc[(*count)])
	{
		if ((hdoc[(*count)] == '<' || hdoc[(*count)] == '>' || \
		hdoc[(*count)] == '\0') && signal == 0)
			return (1);
		else if (hdoc[(*count)] != ' ' || hdoc[(*count)] != '<' || \
		hdoc[(*count)] != '>')
			(*signal) = 1;
		(*count)++;
	}
	return (0);
}

static int	hdoc_without_arg(char *hdoc, char type)
{
	int		count;
	int		signal;
	int		flag[2];

	count = 0;
	signal = 0;
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;
	if (!hdoc)
		return (0);
	while (hdoc[count])
	{
		if (hdoc[count] == type && hdoc[count + 1] != type && \
		flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0)
		{
			count++;
			if (bolean_without_arg(hdoc, &count, &signal))
				return (1);
			if (signal == 0)
				return (1);
		}
		check_quotes(hdoc[count], &flag[P_QUOTE], &flag[S_QUOTE]);
		count++;
	}
	return (0);
}

int	error_cmd(t_cmd_line **node)
{
	if ((*node)->raw_cmd == NULL)
	{
		printf("Myshell: parse error near '|' \n");
		return (1);
	}
	if (hdoc_without_arg((*node)->raw_cmd, '<'))
	{
		printf("Myshell: `<' parse error near \n");
		return (1);
	}
	if (hdoc_without_arg((*node)->raw_cmd, '>'))
	{
		printf("Myshell: `>' parse error near \n");
		return (1);
	}
	return (0);
}
