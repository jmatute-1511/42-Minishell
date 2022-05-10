/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_comand_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:36:26 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/10 21:28:58 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parse_quote(char *str)
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
int check_if_expand(t_myvars *myvars ,char *str)
{
	int  it;
	int expand_len;
	char *path;

	it  = 0;
	expand_len  = 0;
	while (str[it] != ' ' && str[it] != '\f'\
	&& str[it] != '\n' && str[it] != '\r' && \
	str[it] != '\t' && str[it] != '\v' && str[it])
		it++;
	if(it > 0)
	{
		path = find_path(myvars, &str[it], it);
		if(path != NULL)
			expand_len = ft_strlen(path);
		free(path);
		it = 0;
	}
	return(expand_len);
}
int return_len(t_myvars * myvars, char *str)
{
	int count;
	int simple_quote;
	int pair_quote;
	int len;
	
	pair_quote = 0;
	simple_quote = 0;
	count = 0;
	len = 0;
	while (str[count])
	{
		if (str[count] == '"'  && pair_quote == 0 && simple_quote == 0)
			pair_quote++;
		else if (str[count] == '"'  && pair_quote == 1)
		{
			pair_quote--;
			len -= 2;
		}
		if (str[count] == '\''  && simple_quote == 0 && pair_quote == 0)
			simple_quote++;
		else if (str[count] == '\''  && simple_quote == 1)
		{
			simple_quote--;
			len -= 2;
		}
		if (pair_quote == 1 && str[count] == '$')
			len += check_if_expand(myvars,&str[count]);
		if (str[count] == '|' && simple_quote == 0 && pair_quote == 0)
			return(len);
		count++;
		len++;
	}
	return (len);
}


char  *find_path(t_myvars *myvars, char *str, int top)
{
	t_enviroment	*aux;
	char			expand;

	aux  = myvars->my_env;

	while (aux->next)
	{	
		if (ft_strncmp(aux->env_var, str, top))
		{
			expand = ft_strdup(&aux->env_var[top + 1]);
			return (expand);
		}
		aux = aux ->next;
	}
	return (NULL);
}

char * filtered_str(t_cmd_line *line_cmd,t_myvars *myvars, char  str)
{
	
}

int len_newstr(t_myvars *myvars, char *str)
{
	int count;
	int len;
	int aux_len;
	
	count = 0;
}
char *return_str(char *  str)
{
	
}
int	parse_cmd(char *str)
{
	int count;
	
	if(parse_quote(str))
		return (1);
	printf("%d\n",count);
	
}