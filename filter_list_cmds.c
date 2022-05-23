/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_list_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:23:57 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/23 19:11:23 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_quotes(char str, int *pair_quote, int *single_quote)
{
	if (str == '"' && *pair_quote == 0 && *single_quote == 0)
		(*pair_quote) += 1;
	else if (str == '"' && *pair_quote == 1)
		(*pair_quote) -= 1;
	if (str == '\''  && *single_quote == 0 && *pair_quote == 0)
		(*single_quote) += 1;
	else if (str == '\''  && *single_quote == 1)
		(*single_quote) -= 1;
}
void capture_hdoc(t_cmd_line **node, char *raw_cmd)
{
	int	count;
	int	flag[2];

	count  = 0;
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;
	while (raw_cmd[count])
	{
		check_quotes(raw_cmd[count], &flag[P_QUOTE], &flag[S_QUOTE]);
		if(raw_cmd[count] == ' ' && flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0)
		break;
		if(raw_cmd[count] == '<' && flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0)
		{
			
		}
		else if(raw_cmd[count] == '>' && flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0)
		{
			if(raw_cmd[count + 1] == '>')
			{
				count++;
				
			}
					
		}
		count++;
	}
}
int	heredocs_types(t_cmd_line **node)
{
	char	*aux;
	int		count;

	count = 0;
		
	aux = (*node)->raw_cmd;
	
}
void add_first_arg(t_cmd_line **node)
{
	char	*aux;
	int		count;
	int		flag[2];

	count = 0;
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;	
	aux = (*node)->raw_cmd;
	while (aux[count])
	{
		if (flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0 && aux[count] == ' ')
			(*node)->first_arg = ft_strldup(aux, count);			
		check_quotes(aux[count], &flag[P_QUOTE], &flag[S_QUOTE]);
		count++;
	}
}

void	init_components_of_node(t_cmd_line **lst)
{
	t_cmd_line *aux;
	
	aux = (*lst);
	aux->type  =NULL;
	aux->first_arg = NULL;
	aux->arguments  = NULL;
}
void init_node(t_cmd_line **lst_cmds,t_enviroment **myenv,char *str)
{
	t_cmd_line *aux;
	if (first_filter_errors(str))
		return(1);
	*lst_cmds = list_cmds(str);
	aux = (*lst_cmds);
	while (aux)
	{
		init_components_of_node(&aux);
		aux = aux->next;
		if(aux->first_arg == NULL)
		{
			
		}
			
	}
}