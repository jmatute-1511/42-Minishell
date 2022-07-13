/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_list_cmds3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bremesar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:42:50 by bremesar          #+#    #+#             */
/*   Updated: 2022/07/13 14:42:51 by bremesar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_argument(t_cmd_line **node, t_myvars **my_vars)
{
	char	*a;
	char	*b;

	a = NULL;
	b = NULL;
	if ((*node)->arguments)
	{
		a = expand_str((*my_vars), (*node)->arguments);
		free((*node)->arguments);
		(*node)->arguments = a;
	}
	if ((*node)->first_arg)
	{
		b = expand_str((*my_vars), (*node)->first_arg);
		free((*node)->first_arg);
		(*node)->first_arg = b;
	}
	expand_continue(node);
}

void	charge_elements(t_cmd_line **node, t_myvars **my_vars)
{
	char	*aux;
	int		count;
	int		flag[2];

	count = 0;
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;
	aux = (*node)->raw_cmd;
	if (aux)
	{
		capture_arguments(node, aux);
		capture_first_arg(node);
		expand_argument(node, my_vars);
	}
}

int	error_hdoc(t_cmd_line *node)
{
	int	a;

	a = 0;
	if (node->input)
	{
		while (node->input[a] && node->input)
		{
			if (node->input[a] == '<' && \
			(node->input[a + 2] == '<' || node->input[a + 2] == '>'))
				return (1);
			a++;
		}
	}
	a = 0;
	if (node->output)
	{
		while (node->output[a])
		{
			if (node->output[a] == '<' && \
			(node->output[a + 2] == '<' || node->output[a + 2] == '>'))
				return (1);
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
		if (error_hdoc(aux))
			return (1);
		aux = aux->next;
	}
	return (0);
}
