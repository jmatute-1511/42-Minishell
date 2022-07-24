/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 20:38:50 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/24 19:49:26 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**parse_str_unset(char *str)
{
	char	*str_aux;
	char	**split;
	char	*aux;
	int		a;

	a = 0;
	str_aux = ft_strtrim(str, " ");
	split = ft_split(&str_aux[ft_point_strchr(str_aux, ' ')], ' ');
	while (split[a])
	{
		aux = set_quotes(split[a]);
		free(split[a]);
		split[a] = ft_strjoin(aux, "=");
		free(aux);
		a++;
	}
	free(str_aux);
	return (split);
}

void	unset_export_env(t_enviroment **export_env, t_enviroment **aux_export, \
t_enviroment **prev_aux)
{
	if ((*prev_aux) == NULL)
	{
		(*export_env) = (*export_env)->next;
		free((*aux_export));
	}
	else
	{
		(*prev_aux)->next = (*aux_export)->next;
		free((*aux_export));
	}
}

void	unset_myenv(t_enviroment **myenv, t_enviroment **aux_myenv, \
t_enviroment **prev_aux)
{
	if ((*prev_aux) == NULL)
	{
		(*myenv) = (*myenv)->next;
		free((*aux_myenv));
	}
	else
	{
		(*prev_aux)->next = (*aux_myenv)->next;
		free((*aux_myenv));
	}
}

void	bucle_unset_env(char **split, t_enviroment**my_env)
{
	t_enviroment	*aux_myenv;
	t_enviroment	*prev_aux;
	int				point;
	int				a;

	a = 0;
	while (split[a])
	{
		aux_myenv = (*my_env);
		prev_aux = NULL;
		point = ft_point_strchr(split[a], '=');
		while (aux_myenv)
		{
			if (ft_strncmp(aux_myenv->env_var, split[a], point) == 0)
				unset_myenv(my_env, &aux_myenv, &prev_aux);
			prev_aux = aux_myenv;
			aux_myenv = aux_myenv->next;
		}
		a++;
	}
}

void	bucle_unset_export(char **split, t_enviroment **export_env)
{
	t_enviroment	*aux_export;
	t_enviroment	*prev_aux;
	int				point;
	int				a;

	a = 0;
	while (split[a])
	{
		prev_aux = NULL;
		aux_export = (*export_env);
		point = ft_point_strchr(split[a], '=');
		while (aux_export)
		{
			if (ft_strncmp(aux_export->env_var, split[a], point) == 0)
				unset_myenv(export_env, &aux_export, &prev_aux);
			prev_aux = aux_export;
			aux_export = aux_export->next;
		}
		a++;
	}
}

void	built_unset(t_enviroment **myenv, t_enviroment **export_env, char *str)
{
	char	**split;

	split = parse_str_unset(str);
	bucle_unset_env(split, myenv);
	bucle_unset_export(split, export_env);
	free_matrix(split);
}
