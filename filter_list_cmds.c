/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_list_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:23:57 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/31 15:25:50 by jmatute-         ###   ########.fr       */
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
void join_args(t_cmd_line **node, char *str, int count)
{
	char *join;
	char *cut;

	cut = ft_strldup(str, count);
	join = ft_strjoin((*node)->arguments, cut);
	free((*node)->arguments);
	free(cut);
	(*node)->arguments= join;
}
int insert_arg(t_cmd_line **node, char *str)
{
	int count;
	int flag[2];
	
	count = 0;
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;
	while(str[count])
	{
		if ((str[count] == '<' || str[count] == '>' ) && \
		flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0)
			break;
		check_quotes(str[count], &flag[P_QUOTE], &flag[S_QUOTE]);
		count++;
	}
	if ((*node)->arguments != NULL)
		join_args(node, str, count);
	else
		(*node)->arguments = ft_strldup(str, count);
	return(count);
}

void capture_arguments(t_cmd_line **node, char * str)
{
	int count;
	int flag[2];
	int signal;	
	
	count = 0;
	signal = 0;
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;
	while (str[count])
	{
		if((str[count] == '>' || str[count] == '<') && \
		flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0)
		{
			while(str[count] && str[count] == ' ')
				count++;
			signal = 1;
			count++;
		}
		else if (str[count] == ' ' && signal > 0 && flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0)
			signal--;
		else if(str[count] != ' ' &&  signal == 0 && flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0) 
			count += insert_arg(node, &str[count]);
		else
		{
			check_quotes(str[count], &flag[P_QUOTE], &flag[S_QUOTE]);
			count++;
		}
	}
}
void capture_first_arg(t_cmd_line **node)
{
	int count;
	int flag[2];
	char	*str;
	
	count = 0;
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;
	if ((*node)->arguments)
	{
		str = (*node)->arguments;
		while(str[count])
		{
			if (str[count] == ' ' && flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0)
				break;
			check_quotes(str[count], &flag[P_QUOTE], &flag[S_QUOTE]);
			count++;
		}
		(*node)->first_arg = ft_strldup(str, count);
	}
}
void add_first_arg(t_cmd_line **node, t_enviroment **myenv)
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
	capture_arguments(node, aux);
	capture_first_arg(node);
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
		add_first_arg(&aux, myenv);
		if (error_cmd(&aux, myenv))
		{
			printf("error\n");
		}
		aux = aux->next;
	}
} 