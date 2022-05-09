/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:53:04 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/09 17:27:05 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parse_str(char *str)
{
	int count;
	int simple_quote;
	int pair_quote;

	pair_quote = 0;
	simple_quote = 0;
	count = 0;
	while (str[count])
	{
		if (str[count] == '=' && (str[count - 1] == ' ' || str[count + 1] == ' '))
			return(1);
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

void print_env(t_enviroment **my_env)
{
	t_enviroment *aux;

	aux = (*my_env);
	while (aux->next)
	{
		printf("declare -x %s\n",aux->env_var);
		aux = aux->next;
	}
	
}

void built_export(t_enviroment **my_env, char *str)
{
	int same;
	
	if (str == NULL)
		print_env(my_env);
	else if (parse_str(str))
		return ;
	else
		ft_nodeadd_alphabet(my_env,ft_nodenew(str));
}