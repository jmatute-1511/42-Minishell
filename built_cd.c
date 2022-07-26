/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 19:07:46 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/26 16:39:36 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_enviroment	*find_path(t_enviroment *my_env, char *str)
{
	t_enviroment	*aux;

	aux = my_env;
	while (aux)
	{
		if (ft_strncmp(aux->env_var, str, ft_strlen(str)) == 0)
			return (aux);
		aux = aux->next;
	}
	return (NULL);
}

static void	change_location(t_enviroment **env_var, t_enviroment **old_var, \
char *str, char *actual)
{
	char	*current;

	chdir (str);
	current = getcwd(NULL, 0);
	if ((*env_var) != NULL && current != NULL)
	{
		free((*env_var)->env_var);
		(*env_var)->env_var = ft_strjoin ("PWD=", current);
	}
	if ((*old_var)!= NULL && actual != NULL)
	{
		free((*old_var)->env_var);
		(*old_var)->env_var = ft_strjoin("OLDPWD=", actual);
	}
	if (current)
		free(current);
}

void	go_back_home(t_myvars **my_vars)
{
	int				point;
	char			*home;
	char			*current;
	t_enviroment	*aux_home;

	point = 0;
	home = NULL;
	aux_home = find_path((*my_vars)->my_env, "HOME=");
	current = getcwd(NULL, 0);
	if (aux_home)
	{
		point = ft_point_strchr(aux_home->env_var, '=');
		home = ft_strdup(&aux_home->env_var[point + 1]);
		chdir(home);
		if ((*my_vars)->old_pwd)
		{
			free((*my_vars)->old_pwd->env_var);
			(*my_vars)->old_pwd->env_var = ft_strjoin("OLDPWD=", current);
		}
		if ((*my_vars)->pwd)
		{
			free((*my_vars)->pwd->env_var);
			(*my_vars)->pwd->env_var = ft_strjoin("PWD=", home);
		}
	}
	free(current);
	if (home)
		free(home);
}

void	built_cd(t_myvars **myvars, char *str)
{
	int				point;
	char			*trim;
	char			*actual;
	t_enviroment	*pwd;
	t_enviroment	*old_pwd;

	point = ft_point_strchr(str, ' ');
	trim = ft_strtrim(&str[point], " ");
	if (trim == NULL)
		go_back_home(myvars);
	if (access(trim, X_OK) != 0 || (*myvars)->my_env == NULL)
		return ;
	actual = getcwd(NULL, 0);
	pwd = find_path((*myvars)->my_env, "PWD=");
	old_pwd = find_path((*myvars)->my_env, "OLDPWD=");
	change_location(&pwd, &old_pwd, trim, actual);
	if (actual)
		free(actual);
	if (trim)
		free(trim);
}
