/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bremesar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:24:36 by bremesar          #+#    #+#             */
/*   Updated: 2022/07/08 14:24:39 by bremesar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_enviroment *export_env, char *option)
{
	t_enviroment	*aux;

	aux = export_env;
	while (aux)
	{
		if (ft_strcmp("env", option) == 0)
			printf("%s\n", aux->env_var);
		else if (ft_strcmp("export", option) == 0)
			printf("declare -x %s\n", aux->env_var);
		aux = aux->next;
	}
}

int	size_of_lst(t_cmd_line **lst)
{
	int			a;
	t_cmd_line	*aux;

	a = 0;
	aux = (*lst);
	while (aux)
	{
		aux = aux->next;
		a++;
	}
	return (a);
}
