/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:24:36 by bremesar          #+#    #+#             */
/*   Updated: 2022/07/24 19:41:50 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_point_strchr(char *s, char c)
{
	size_t		count;
	char		*cpy_s;

	cpy_s = (char *)s;
	count = 0;
	while (cpy_s[count] && cpy_s[count] != c)
		count++;
	if (cpy_s[count] != '\0')
		return (count);
	else
		return (ft_strlen(s));
}

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
