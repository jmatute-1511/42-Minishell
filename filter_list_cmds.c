/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_list_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:23:57 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/26 18:08:16 by jmatute-         ###   ########.fr       */
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
	line = ft_strchrdup_quote(&output[count], " <>");
	if (line  != NULL)
	{
		if ((*node)->output  && type[0] == '>')
		{
			trim = ft_strnjoin(5,(*node)->output," ", type, " ", line);
			free((*node)->output);
		}
		else if((*node)->input && type[0] == '<')
		{
			trim = ft_strnjoin(5,(*node)->input," ", type, " ", line);
			free((*node)->input);
		}
		else
			trim = ft_strnjoin(3, type, " ", line);
		if (type[0] == '<')
			(*node)->input = ft_strtrim(trim, " ");
		else if (type[0] == '>')
			(*node)->output = ft_strtrim(trim, " ");
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
		{
			type = select_type_hdoc( &str[count]);
			add_hdoc(node, type, &str[count]);
			free(type);	
			if(str[count + 1] == '<')
				count++;
		}
		check_quotes(str[count], &flag[P_QUOTE], &flag[S_QUOTE]);
		count++;
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
		{
			type = select_type_hdoc( &str[count]);
			add_hdoc(node, type, &str[count]);
			free(type);
			if (str[count + 1] == '>')
				count++;
		}
		check_quotes(str[count], &flag[P_QUOTE], &flag[S_QUOTE]);
		count++;
	}
	
}
void init_flags(int *pairquote, int *singlequote, int *first, int *final)
{
	*pairquote = 0;
	*singlequote = 0;
	*first = 0;
	*final = 0;
}
int bolean_input(char *str, int *count)
{
	if(str[*count] == '<' && *signal == 0)
	{
		if(str[*count + 1] =='<')
			count++;
		return(1);
	}
	return(0);
}
int bolean_output(char *str, int count)
{
	
	
}
void capture_arguments(t_cmd_line **node, char *str)
{
	int count;
	int flag[2];
	int sign[2];
	int signal;
	
	count = 0;
	signal = 0;
	init_flags(&flag[P_QUOTE], &flag[S_QUOTE], &sign[FIRST], &sign[FINAL]);
	while (str[count])
	{
		if (flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0)
		{
			if (bolean_input(&str[count], &count))
				signal++;
			else if ()
			
		}
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