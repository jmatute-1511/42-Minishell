/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:53:04 by jmatute-          #+#    #+#             */
/*   Updated: 2022/06/18 15:39:32 by jmatute-         ###   ########.fr       */
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

int error_export(char **split)
{
	int a;
	char *str;

	a = 0;
	while(split[a])
	{
		if(ft_strchr(split[a], ' ') != NULL)
		{
			str = set_quotes(split[a]);
			printf("bash: export: `%s': not a valid identifier\n",str);
			free(str);
			return(1);
		}
		a++;
	}
	return (0);
}
void export_vars(char **split, t_enviroment **my_env, t_enviroment **export_env)
{
	int	a;
	char	*str;
	
	a  = 0;
	while (split[a])
	{
		str = set_quotes(split[a]);
		if (ft_strchr(split[a], '=') != NULL)
		{	
			set_or_new_node_env(my_env, str);
			set_or_new_node_export(export_env,str);
		}
		else if (ft_strchr(split[a], '=')  == NULL )
			set_or_new_node_export(export_env,str);
		if (str != NULL)
			free(str);
		a++;
	}
}
void built_export(t_enviroment **my_env,t_enviroment **export_env, char *str)
{
	char 			*trim;
	int				point;
	char			**split;
	
	point = ft_point_strchr(str, ' ');
	trim = ft_strtrim(&str[point], " ");
	
	if (trim != NULL)
	{
		split = ft_split_ignore(trim, ' ', "\"'");
		if (error_export(split) == 0)
			export_vars(split, my_env, export_env);
		free_matrix(split);
	}
	else if(trim == NULL)
		print_env(*export_env,"export");
	free(trim);
}