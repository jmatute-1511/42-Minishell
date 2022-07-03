/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 12:14:18 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/03 19:17:46 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_chr(char c)
{
	if (c == ' ' || c == '$' || c == '\'' || c == '"')
		return (1);
	else if(ft_isalpha(c) == 0 && ft_isalnum(c) == 0)
		return (1);
	return (0);
}

int ft_point_strstr(char *str)
{
	
	int count_str;

	count_str = 0;
	while(str[count_str])
	{
		if (check_chr(str[count_str]))
			return(count_str);
		count_str++;   
	}
	return (count_str);
}
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
int	comp_with_string(char chr, char *str)
{
	int count;
	int count2;

	count = 0;
	count2 = 0;
	while (str[count])
	{
		if(str[count] == chr)
			return(1);
		count++;
	}
	return(0);
}
char *ft_strchrdup_quote(char *str,char *chr)
{
	int     count;
	char    *line;
	int		flag[2];	
	
	count = 0;
	line = NULL;
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;
	while (str[count])
	{
		if (ft_strchr(chr, str[count]) != NULL && \
		flag[P_QUOTE] == 0 &&  flag[S_QUOTE] == 0)
			break;
		check_quotes(str[count], &flag[P_QUOTE], &flag[S_QUOTE]);
		count++;
	}
	if(count != 0)
		line = ft_strldup(str, count);
	return (line);
}
void print_env(t_enviroment *export_env, char *option)
{
	t_enviroment *aux;

	aux = export_env;
	while (aux)
	{
		if (ft_strcmp("env", option) == 0)
			printf("%s\n",aux->env_var);
		else if (ft_strcmp("export", option) == 0)
			printf("declare -x %s\n",aux->env_var);
		aux = aux->next;
	}
}
int size_of_lst(t_cmd_line **lst)
{
	int a;
	t_cmd_line *aux;

	a = 0;
	aux = (*lst);
	while(aux)
	{
		aux = aux->next;
		a++;
	}
	return(a);
}