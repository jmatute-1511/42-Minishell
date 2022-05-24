/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_list_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:23:57 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/24 19:18:47 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char *select_type_hdoc(char  *raw_cmd)
{
	int count;

	count = 0;
	if (raw_cmd[count] == '>' && raw_cmd[count + 1] != '>')
		return(ft_strdup(">"));
	else if (raw_cmd[count] == '<' && raw_cmd[count + 1] != '<')
		return(ft_strdup("<"));
	else if (raw_cmd[count] == '<' && raw_cmd[count + 1] == '<')
		return(ft_strdup("<<"));
	else if (raw_cmd[count] == '>' && raw_cmd[count + 1] == '>')
		return(ft_strdup(">>"));
	return(NULL);
}

void capture_hdoc(t_cmd_line **node, char *raw_cmd)
{
	int	count;
	char *type;	
	char *line;

	count = 0;
	type = select_type_hdoc(raw_cmd);
	if (type == NULL)
		return;
	if (raw_cmd[count + 1] == ' ')
		count += 1;
	else if (raw_cmd[count + 2] == ' ')
		count += 2;
	else
		count = 1;	 
	while(raw_cmd[count] == ' ')
		count++;
	line = ft_strchrdup_quote(&raw_cmd[count], ' ');
	if(line != NULL)
	{
		(*node)->first_arg = ft_strnjoin(3, type, " ", line);
		(*node)->type = ft_strdup(type);
		free(type);
		free(line);
	}
}

void capture_program(t_cmd_line  **node, char *raw_cmd)
{
	int count;
	int flag[2];

	count = 0;
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;
	while (raw_cmd[count])
	{
		if (raw_cmd[count] == ' ' && flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0)
		{
			(*node)->first_arg = ft_strldup(raw_cmd, count);
			(*node)->type = set_quotes((*node)->first_arg);
			break;
		}
		check_quotes(raw_cmd[count], &flag[P_QUOTE], &flag[S_QUOTE]);
		count++;
	}
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
	capture_hdoc(node, aux);
	if ((*node)->first_arg == NULL)
		 capture_program(node, aux);
}

void init_nodes(t_cmd_line **lst_cmds,t_enviroment **myenv,char *str)
{
	t_cmd_line *aux;
	if (first_filter_errors(str))
	{
		dprintf(1, "ERROR\n");	
		return;
	}
	*lst_cmds = list_cmds(str);
	aux = (*lst_cmds);
	while (aux)
	{
		add_first_arg(&aux);
		aux = aux->next;
	}
} 