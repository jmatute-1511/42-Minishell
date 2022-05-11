/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:53:04 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/11 21:58:58 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_point_strchr(const char *s, int c)
{
	size_t		count;
	char		*cpy_s;
	int 		len;

	cpy_s = (char *)s;
	count = 0;
	len = ft_strlen(s);
	while (count <= len)
	{
		if (cpy_s[count] == (char)c)
			return (count);
		count++;
	}
	return (0);
}

void set_or_new_node_env(t_enviroment *my_env, char *str)
{
	t_enviroment *aux;

	aux = my_env;
	while (aux->next)
	{
		if (ft_strncmp(aux->env_var, str, ft_point_strchr(str, '=')))
		{
			free(aux->env_var);
			aux->env_var = ft_strdup(str);
		}
		aux = aux->next;
	}
	if (ft_strncmp(aux->env_var, str, ft_point_strchr(str, '=')))
	{
		free(aux->env_var);
		aux->env_var = ft_strdup(str);
	}
	else if (aux->next == NULL)
		ft_nodeadd_back(&my_env, ft_nodenew(str));
}

void set_or_new_node_export(t_enviroment *export_env, char *str)
{
	t_enviroment *aux;

	aux = export_env;
	while (aux->next)
	{
		if (ft_strncmp(aux->env_var, str, ft_point_strchr(str, '=')))
		{
			free(aux->env_var);
			aux->env_var = ft_strdup(str);
		}
		aux = aux->next;
	}
	if (ft_strncmp(aux->env_var, str, ft_point_strchr(str, '=')))
	{
		free(aux->env_var);
		aux->env_var = ft_strdup(str);
	}
	else if (aux->next == NULL)
		ft_nodeadd_back(&export_env, ft_nodenew(str));
}

void print_env(t_enviroment *export_env)
{
	t_enviroment *aux;

	aux = export_env;
	while (aux)
	{
		printf("declare -x %s\n",aux->env_var);
		aux = aux->next;
	}
}

void built_export(t_enviroment **my_env,t_enviroment **export_env, char *str)
{
	int same;
	
	if (ft_strchr(str, '=') != NULL)
	{
		ft_putstr_fd("ENTRE", 1);
		//set_or_new_node_env(*my_env, str);
		//set_or_new_node_export(*export_env, str);
		print_env(*my_env);
		print_env(*export_env);
	}
	else if (ft_strchr(str, '=') == NULL)
	{
		ft_nodeadd_alphabet(export_env, ft_nodenew(str));
		print_env(*export_env);
	}
}