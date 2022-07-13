/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_list_cmds2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bremesar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:42:41 by bremesar          #+#    #+#             */
/*   Updated: 2022/07/13 14:42:42 by bremesar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_argument_quotes(char *str, int flag[2])
{
	int		count;

	count = 0;
	while (str[count])
	{
		if ((str[count] == '<' || str[count] == '>') && \
		flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0)
			break ;
		check_quotes(str[count], &flag[P_QUOTE], &flag[S_QUOTE]);
		count++;
	}
	return (count);
}

int	add_arguments(t_cmd_line **node, char *str)
{
	char	*name;
	char	*join;
	int		count;
	int		flag[2];

	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;
	count = check_argument_quotes(str, flag);
	if ((*node)->arguments)
	{
		name = ft_strldup(str, count);
		join = ft_strnjoin(3, (*node)->arguments, " ", name);
		free((*node)->arguments);
		(*node)->arguments = join;
		free(name);
	}
	else
		(*node)->arguments = ft_strldup(str, count);
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

void	expand_continue(t_cmd_line **node)
{
	char	*c;

	c = NULL;
	if ((*node)->input)
	{
		c = set_quotes((*node)->input);
		free((*node)->input);
		(*node)->input = c;
	}
	if ((*node)->output)
	{
		c = set_quotes((*node)->output);
		free((*node)->output);
		(*node)->output = c;
	}	
}
