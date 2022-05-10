/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_comand_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:36:26 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/10 17:55:43 by jmatute-         ###   ########.fr       */
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

int return_len(char *str)
{
	int count;
	int simple_quote;
	int pair_quote;
	int rest;
	int	expand_len;

	pair_quote = 0;
	simple_quote = 0;
	count = 0;
	rest  = 0;
	while (str[count])
	{
		if (str[count] == '"'  && pair_quote == 0 && simple_quote == 0)
			pair_quote++;
		else if (str[count] == '"'  && pair_quote == 1)
		{
			pair_quote--;
			rest += 2;
		}
		if (str[count] == '\''  && simple_quote == 0 && pair_quote == 0)
			simple_quote++;
		else if (str[count] == '\''  && simple_quote == 1)
		{
			simple_quote--;
			rest += 2;
		}
		if (pair_quote == 1 && str[count] == '$')
		{
			while ()
			{
				/* code */
			}
			
		}
		if (str[count] == '|' && simple_quote == 0 && pair_quote == 0)
			return(count - rest);
		count++;
	}
	return (count - rest);
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
			expand = ft_strdup(&aux->env_var[top]);
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
	count = return_len(str);
	printf("%d\n",count);
	
}