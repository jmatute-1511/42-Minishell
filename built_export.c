/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:53:04 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/22 12:24:01 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_point_strchr(char *s, char c)
{
	size_t		count;
	char		*cpy_s;

	cpy_s = (char *)s;
	count = 0;
	while (cpy_s[count] && cpy_s[count] != c)
		count++;
	if (cpy_s[count] != '\0')
		return(count);
	else
		return (ft_strlen(s));
}

void set_or_new_node_env(t_enviroment **my_env, char *str)
{
	t_enviroment *aux;
	t_enviroment *new;

	aux = (*my_env);
	while (aux)
	{
		if (ft_strncmp(aux->env_var, str, ft_point_strchr(str, '=')) == 0)
		{
			free(aux->env_var);
			aux->env_var = ft_strdup(str);
			break;
		}
		else if (aux->next == NULL)
		{
			new = ft_nodenew(str);
			ft_nodeadd_back(my_env,&new);
		}
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
		if (ft_strncmp(aux->env_var, str, ft_point_strchr(str, '=')) == 0)
		{
			free(aux->env_var);
			aux->env_var = ft_strdup(str);
			break;
		}
		else if (aux->next == NULL)
		{
			new = ft_nodenew(str);
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
	t_enviroment *new;
	char 			*trim;
	
	trim = ft_strtrim(str, " ");
	if (ft_strchr(str, '=') != NULL)
	{	
		set_or_new_node_env(my_env, trim);
		set_or_new_node_export(export_env,trim);
	}
	else if (ft_strchr(str, '=') == NULL)
	{
		new = ft_nodenew(trim);
		set_or_new_node_export(export_env,trim);
	}
	print_env(*my_env, "env");
	printf("\n");
	print_env(*export_env,"export");
	free(trim);
}