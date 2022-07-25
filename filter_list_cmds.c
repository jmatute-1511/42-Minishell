/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_list_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:23:57 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/24 20:33:29 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_argument(t_cmd_line **node, t_myvars **my_vars)
{
	char	*c;

	if ((*node)->arguments)
		(*node)->arguments = expansions(&(*node)->arguments, my_vars);
	if ((*node)->first_arg)
		(*node)->first_arg = expansions(&(*node)->first_arg, my_vars);
	if ((*node)->output)
	{
		c = set_quotes((*node)->output);
		free((*node)->output);
		(*node)->output = c;
	}
}

void	charge_elements(t_cmd_line **node, t_myvars **my_vars)
{
	char	*aux;
	int		count;	

	count = 0;
	aux = (*node)->raw_cmd;
	if (aux)
	{
		capture_arguments(node, aux);
		expand_argument(node, my_vars);
		capture_first_arg(node);
	}
}

int	error_hdoc(char *str, char type, char c_type)
{
	int	a;

	a = 0;
	if (str)
	{
		while (str[a] && str)
		{
			if (str[a] == type && (str[a + 2] == type || \
			str[a + 2] == c_type || str[a + 2] == '\0'))
			{
				printf("Myshell: parse error near `%c'\n", type);
				return (1);
			}
			if (str[a] == type && str[a + 1] == type)
				a++;
			a++;
		}
	}
	return (0);
}

int	init_nodes(t_cmd_line **lst_cmds, t_myvars **my_vars, char *str)
{
	t_cmd_line	*aux;

	if (first_filter_errors(str))
		return (1);
	*lst_cmds = list_cmds(str);
	aux = (*lst_cmds);
	while (aux)
	{
		charge_elements(&aux, my_vars);
		if (error_hdoc(aux->input, '<', '>') || \
		error_hdoc(aux->input, '>', '<') || error_cmd(&aux))
			return (1);
		aux = aux->next;
	}
	return (0);
}
