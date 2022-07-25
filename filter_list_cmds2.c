/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_list_cmds2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bremesar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:44:31 by bremesar          #+#    #+#             */
/*   Updated: 2022/07/25 17:44:33 by bremesar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	complement_add_arguments(t_cmd_line **node, char *str, int count)
{
	char	*name;
	char	*join;

	if ((*node)->arguments)
	{
		name = ft_strldup(str, count);
		join = ft_strnjoin(3, (*node)->arguments, " ", name);
		free((*node)->arguments);
		(*node)->arguments = NULL;
		(*node)->arguments = join;
		free(name);
	}
	else
		(*node)->arguments = ft_strldup(str, count);
}

int	add_arguments(t_cmd_line **node, char *str)
{
	int	count;
	int	flag[2];

	count = 0;
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;
	while (str[count])
	{
		if ((str[count] == '<' || str[count] == '>') && \
		flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0)
			break ;
		check_quotes(str[count], &flag[P_QUOTE], &flag[S_QUOTE]);
		count++;
	}
	complement_add_arguments(node, str, count);
	return (count - 1);
}

void	capture_arguments(t_cmd_line **node, char *str)
{
	int	count;
	int	flag[2];

	count = 0;
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;
	while (str[count])
	{
		if (flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0)
		{
			if (str[count] == '<' || str[count] == '>')
				count += add_hdocs(node, &str[count]);
			else if (str[count] != ' ')
				count += add_arguments(node, &str[count]);
		}
		check_quotes(str[count], &flag[P_QUOTE], &flag[S_QUOTE]);
		count++;
	}
}

void	capture_first_arg(t_cmd_line **node)
{
	int		count;
	int		flag[2];
	char	*str;

	count = 0;
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;
	if ((*node)->arguments)
	{
		str = (*node)->arguments;
		while (str[count])
		{
			if (str[count] == ' ' && flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0)
				break ;
			check_quotes(str[count], &flag[P_QUOTE], &flag[S_QUOTE]);
			count++;
		}
		(*node)->first_arg = ft_strldup(str, count);
	}
}

char	*expansions( char **str, t_myvars **my_vars)
{
	char	*expanded;

	expanded = expand_str((*my_vars), (*str));
	free((*str));
	return (expanded);
}
