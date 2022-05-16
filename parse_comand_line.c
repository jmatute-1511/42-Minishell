/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_comand_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:36:26 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/16 19:53:43 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_quotes(char *str)
{
	int count;
	int simple_quote;
	int pair_quote;

	pair_quote = 0;
	simple_quote = 0;
	count = 0;
	while (str[count] )
	{
		if (str[count] == '"'  && pair_quote == 0 && simple_quote == 0)
			pair_quote++;
		else if (str[count] == '"'  && pair_quote == 1)
			pair_quote--;
		if (str[count] == '\''  && simple_quote == 0 && pair_quote == 0)
			simple_quote++;
		else if (str[count] == '\''  && simple_quote == 1)
			simple_quote--;
		count++;
	}
	if (pair_quote != 0  || simple_quote != 0)
		return (1);
	return (0);
}

int check_is_spaces(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f' || c == '\r'  || c == '$')
		return (1);
	return (0);
}

char *get_expand(char *str)
{
	int 	count;
	int 	flag;
	char	*aux;

	count = 0;
	flag = check_is_spaces(str[count]);
	while (str[count] && flag != 1)
	{	
		count++;
		flag = check_is_spaces(str[count]);
	}
	if (count > 0)
	{
		aux = malloc(sizeof(char) * count + 2);
		count = 0;
		while (aux[count] < count)
		{
			aux[count] = str[count]; 
			count++;
		}
		aux[count] = '=';
		aux[count + 1] = '\0';
		return(aux);
	}
	return(NULL);
}

char  *find_path_expand(t_enviroment **my_env, char *str)
{
	t_enviroment	*aux;
	char			*str_aux;
	char			*expand;
	
	str_aux = get_expand(str);
	aux  = *my_env;	
	expand = NULL;
	while (aux->next)
	{	
		if (ft_strncmp(aux->env_var, str_aux, ft_point_strchr(str_aux, '=')) == 0)
		{
			expand = ft_strdup(&aux->env_var[ft_strlen(str_aux) + 1]);
			free(str_aux);
			break ;
		}
		aux = aux ->next;
	}
	return (expand);
}
int check_if_quote(char chr, int *flag)
{
	if (chr == '"'  && flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0)
		flag[P_QUOTE]++;
	else if (chr == '"'  && flag[P_QUOTE]== 1)
	{
		flag[P_QUOTE]--;
		return (2);
	}
	if (chr == '\''  && flag[S_QUOTE] == 0 && flag[P_QUOTE] == 0)
		flag[S_QUOTE]++;
	else if (chr == '\''  && flag[S_QUOTE] == 1)
	{
		flag[S_QUOTE]--;
		return (2);
	}
	return (0);
}

int len_before_pipe(t_enviroment **myenv,char *str)
{
	int		count;
	char	*expand;
	int		flag[2];
	int 	len;

	count  = 0;
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;
	len = 0;
	while(str[count])
	{
		if (flag[P_QUOTE] == 1 && str[count] == '$')
		{
			expand  = find_path_expand(myenv,&str[count + 1]);
			len += ft_strlen(expand);
			free(expand);
		}
		len -= check_if_quote(str[count], &flag);
		if (str[count] == '|' && flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0)
			break;
		count++;
		len++;
	}
	return(len);
}

char 	*filtered_cmd(t_enviroment **myenv, char *str)
{
	char	*expand;
	int		flag[2];
	char	*line;
	int 	count;
	int		count2;
	int		len;
	int 	a;

	len = len_before_pipe(myenv, str);
	line = malloc(sizeof(char) * len + 1);
	while (str[count])
	{
		if(flag[P_QUOTE] == 1)
		{
			if(str[count] == '$')
				expand = find_path_expand(myenv, &str[count]);
			if (expand != NULL)
			{
				while (line[count2 + a] && expand[a])
				{
					line[count2] = expand[a];
					count2++;
					a++;
				}
				while (str[count])
				{
					if (check_is_spaces(&str[count + 1]))
						break;
					count++;
				}
			}
		}
		check_if_quote(str[count], &flag);
		if (str[count] == '|' && flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0)
			break;
		line[count2] = str[count];
		count2++;
		count++;
	}	
}

char *line_cmd_is_ok(t_enviroment **myenv, char *str)
{
	char	*line;

	line = len_before_pipe(myenv, str);
	
	
}

int parse_cmd_line(char *str)
{
	
}