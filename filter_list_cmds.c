/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_list_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:23:57 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/25 13:59:42 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_hdoc(t_cmd_line **node, char *type, char *output)
{
	char *line;
	int count;
	char *trim;

	count = ft_strlen(type);
	while (output[count] == ' ' && output[count])
		count++;
	line = ft_strchrdup_quote(&output[count], ' ');
	if (line  != NULL)
	{
		if (type[0] == '<')
		{
			trim = ft_strnjoin(3, type, " ", line);
			(*node)->input = ft_strtrim(trim, " ");
		}
		else if (type[0] == '>')
		{
			trim = ft_strnjoin(3, type, " ", line);
			(*node)->output = ft_strtrim(trim, " ");
		}
		free(line);
		free(trim);
	}
}
char *select_type_hdoc(char  *raw_cmd)
{
	int count;

	count = 0;
	if (raw_cmd[count] == '<' && raw_cmd[count + 1] != '<')
		return(ft_strdup("<"));
	else if (raw_cmd[count] == '<' && raw_cmd[count + 1] == '<')
		return(ft_strdup("<<"));
	else if (raw_cmd[count] == '>' && raw_cmd[count + 1] != '>')
		return(ft_strdup(">"));
	else if (raw_cmd[count] == '>' && raw_cmd[count + 1] == '>')
		return(ft_strdup(">>"));
	return(NULL);
}
void  select_hdoc_input(t_cmd_line **node, char *str)
{
	int count;
	int flag[2];
	char *type;
	
	count  = 0;
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;
	while (str[count])
	{
		if (str[count] == '<'  && flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0)
			break;
		check_quotes(str[count], &flag[P_QUOTE], &flag[S_QUOTE]);
		count++;
	}
	if (count < ft_strlen(str))
	{
		type = select_type_hdoc( &str[count]);
		add_hdoc(node, type, &str[count]);
		free(type);
	}
}
void  select_hdoc_output(t_cmd_line **node, char *str)
{
	int count;
	int flag[2];
	char *type;
	
	count  = 0;
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;
	while (str[count])
	{
		if (str[count] == '>'  && flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0)
			break;
		check_quotes(str[count], &flag[P_QUOTE], &flag[S_QUOTE]);
		count++;
	}
	if (count < ft_strlen(str))
	{
		type = select_type_hdoc( &str[count]);
		add_hdoc(node, type, &str[count]);
		free(type);
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
	select_hdoc_input(node, aux);
	select_hdoc_output(node, aux);
	capture_program (node, aux);
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