/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_list_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:23:57 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/04 13:00:12 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void add_input(t_cmd_line **node, char *type, char *output, int count)
{
	char *name;
	char *join;
	
	name = ft_strldup(output,count);
	if ((*node)->input)
	{
		join = ft_strnjoin(4, (*node)->input, type, " ", name);
		free((*node)->input);
		(*node)->input = join;
	}
	else
		(*node)->input = ft_strnjoin(3, type, " ", name);
	free (name);
}

void add_output(t_cmd_line **node, char *type, char *output, int count)
{
	char *name;
	char *join;
	
	name = ft_strldup(output,count);
	if ((*node)->output)
	{
		join = ft_strnjoin(4, ((*node)->output),type, " ", name);
		free((*node)->output);
		(*node)->output = join;
	}
	else
		(*node)->output = ft_strnjoin(3, type, " ", name);
	free(name);
}

int add_types_hdocs(t_cmd_line **node, char *type, char *output)
{
	int count;
	int flag[2];
	
	count  = 0;
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;
	if(output[count])
	{
		while(output[count])
		{
			if (output[count] == ' ' && flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0)
				break;
			check_quotes(output[count], &flag[P_QUOTE], &flag[S_QUOTE]);
			count++;
		}
		if (type[0] == '<')
			add_input(node, type, output, count);
		else if (type[0] == '>')
			add_output(node, type, output, count);
	}
	return(count);
}

int add_hdocs(t_cmd_line **node, char *str)
{
	int count;
	char *type;

	type = select_type_hdoc(str);
	count = ft_strlen(type);
	while (str[count] == ' ')
		count++;
	count += add_types_hdocs(node, type, &str[count]);
	free(type);
	return (count);
}
int add_arguments(t_cmd_line **node, char *str)
{
	char *name;
	char *join;
	int count;
	int flag[2];
	
	count  = 0;
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;
	while (str[count])
	{
		if ((str[count]  == '<' || str[count] == '>') && \
		flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0)
			break;
		check_quotes(str[count], &flag[P_QUOTE], &flag[S_QUOTE]);
		count++;
	}
	if((*node)->arguments)
	{
		name = ft_strldup(str, count);
		join = ft_strnjoin(3, (*node)->arguments, " ", name);
		free((*node)->arguments);
		(*node)->arguments = join;
		free(name);
	}
	else 
		(*node)->arguments= ft_strldup(str, count);
	return (count - 1);
}

void capture_arguments(t_cmd_line **node, char *str)
{
	int count;
	int aux_count;
	int flag[2];
	char *type;
	
	count  = 0;
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;
	while (str[count])
	{
		if(flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0)
		{
			if(str[count] == '<' || str[count] == '>')
				count += add_hdocs(node, &str[count]);
			else if (str[count] != ' ')
				count += add_arguments(node, &str[count]);
		}
		check_quotes(str[count], &flag[P_QUOTE], &flag[S_QUOTE]);
		count++;
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
void charge_elements(t_cmd_line **node, t_enviroment **myenv)
{
	char	*aux;
	int		count;
	int		flag[2];

	count = 0;
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;	
	aux = (*node)->raw_cmd;
	if(aux)
	{
		capture_arguments(node, aux);
		capture_first_arg(node);
	}
}

int init_nodes(t_cmd_line **lst_cmds,t_enviroment **myenv,char *str)
{
	t_cmd_line	*aux;
	char		*str2;
	
	if (first_filter_errors(str))	
		return (1);
	*lst_cmds = list_cmds(str);
	aux = (*lst_cmds);
	while (aux)
	{
		charge_elements(&aux, myenv);
		aux = aux->next;
	}
	return (0);
} 