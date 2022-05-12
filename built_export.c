/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:53:04 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/12 22:29:05 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_point_strchr(const char *s, int c)
{
	size_t		count;
	char		*cpy_s;

	cpy_s = (char *)s;
	count = 0;
	while (cpy_s[count])
	{
		if (cpy_s[count] != (char)c)
			return (count);
		count++;
	}
	return (0);
}

void set_or_new_node_env(t_enviroment **my_env, char *str)
{
	t_enviroment *aux;

	aux = (*my_env);
	while (aux)
	{
		if (ft_strncmp(aux->env_var, str, ft_point_strchr(str, '=') + 1) == 0)
		{
			if (ft_strchr(aux->env_var, '=') != NULL && ft_strchr(str, '=') != NULL)
			{
				free(aux->env_var);
				aux->env_var = ft_strdup(str);
				break;
			}
		}
		else if (aux->next == NULL)
			ft_nodeadd_back(my_env,ft_nodenew(ft_strdup(str)));
		aux = aux->next;
	}
}

void set_or_new_node_export(t_enviroment **export_env, char *str)
{
	t_enviroment *aux;
	t_enviroment *new;

	aux = (*export_env);
	while (aux)
	{
		if (ft_strncmp(aux->env_var, str, ft_point_strchr(str, '=') + 1) == 0)
		{
			if (ft_strchr(aux->env_var, '=') != NULL && ft_strchr(str, '=') != NULL)
			{
				free(aux->env_var);
				aux->env_var = ft_strdup(str);
				break;
			}
			else if (ft_strchr(aux->env_var, '=') == NULL && ft_strchr(str, '=') != NULL)
			{
				free(aux->env_var);
				aux->env_var = ft_strdup(str);
				break;
			}
		}
		else if (aux->next == NULL)
		{
			new = ft_nodenew(ft_strdup(str));
			ft_nodeadd_alphabet(export_env,&new);
		}
		aux = aux->next;
	}
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

void built_export(t_enviroment **my_env,t_enviroment **export_env, char *str)
{
	int same;
	int i;
	t_enviroment *new;
	
	if (ft_strchr(str, '=') != NULL)
	{	
		i = ft_point_strchr(str, ' ');
		set_or_new_node_env(my_env, &str[i]);
		set_or_new_node_export(export_env, &str[i]);
		print_env(*my_env, "env");
		//printf("\n=======================================================================\n");
		print_env(*export_env, "export");
	}
	else if (ft_strchr(str, '=') == NULL)
	{
		new = ft_nodenew(str);
		set_or_new_node_export(export_env, str);
		print_env(*my_env, "env");
		print_env(*export_env, "export");
	}
}