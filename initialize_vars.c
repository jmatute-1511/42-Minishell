/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:13:30 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/24 20:38:34 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_enviroment	*create_export_env(char **envp)
{
	t_enviroment	*export_env;
	t_enviroment	*new;
	int				count;

	count = 0;
	export_env = NULL;
	if (envp == NULL)
		return (NULL);
	while (envp[count])
	{
		new = ft_nodenew(envp[count]);
		ft_nodeadd_alphabet(&export_env, &new);
		count++;
	}
	return (export_env);
}

t_enviroment	*create_env(char **envp)
{
	t_enviroment	*my_env;
	t_enviroment	*new;
	int				count;

	count = 0;
	my_env = NULL;
	if (envp == NULL)
		return (NULL);
	while (envp[count])
	{
		new = ft_nodenew(envp[count]);
		ft_nodeadd_back(&my_env, &new);
		count++;
	}
	return (my_env);
}

int	ft_env_size(t_enviroment *my_env)
{
	int	a;

	a = 0;
	while (my_env)
	{
		my_env = my_env->next;
		a++;
	}
	return (a);
}

char	**enviroment_matrix(t_enviroment *my_env)
{
	int		it;
	int		size;
	char	**m_envp;

	it = 0;
	size = ft_env_size(my_env);
	m_envp = (char **)malloc(sizeof(char *) * size + 1);
	while (my_env)
	{
		m_envp[it] = ft_strdup(my_env->env_var);
		my_env = my_env->next;
		it++;
	}
	m_envp[it] = NULL;
	return (m_envp);
}

char	**create_env_if_not_env(void)
{
	char	**my_envp;

	my_envp = (char **)malloc(sizeof(char *) * 4);
	if (!my_envp)
		return (NULL);
	my_envp[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
	my_envp[1] = ft_strdup("SHLVL=2");
	my_envp[2] = ft_strdup("_=/usr/bin/env");
	my_envp[3] = NULL;
	return (my_envp);
}

void	enviroment_free(t_enviroment *vars_env)
{
	t_enviroment	*aux;

	aux = vars_env;
	while (vars_env)
	{
		vars_env = vars_env->next;
		free(aux->env_var);
		free(aux);
		aux = vars_env;
	}
}

void	free_vars(t_myvars **my_vars)
{
	if ((*my_vars)->first_pwd)
		free((*my_vars)->first_pwd);
	if ((*my_vars)->export_env)
		enviroment_free((*my_vars)->export_env);
	if ((*my_vars)->my_env)
		enviroment_free((*my_vars)->my_env);
	(*my_vars)->pwd = NULL;
	(*my_vars)->old_pwd = NULL;
	(*my_vars)->home = NULL;
}

void	change_ucmd(t_enviroment **myenv, t_enviroment **export_env)
{
	t_enviroment	*aux_env;
	t_enviroment	*export_aux;

	aux_env = find_path((*myenv), "_=");
	export_aux = find_path((*export_env), "_=");
	if (aux_env)
	{
		free(aux_env->env_var);
		aux_env->env_var = ft_strdup("_=/usr/bin/env");
	}
	if (export_aux)
	{
		free(export_aux->env_var);
		export_aux->env_var = ft_strdup("_=/usr/bin/env");
	}
}

t_myvars	*start_vars(t_myvars *myvars, char **envp)
{
	char	**my_envp;
	char	**now_env;

	now_env = envp;
	if (!*envp)
	{
		my_envp = NULL;
		my_envp = create_env_if_not_env();
		now_env = my_envp;
	}
	myvars = malloc(sizeof(t_myvars));
	myvars->first_pwd = getcwd(NULL, 0);
	myvars->export_env = create_export_env(now_env);
	myvars->my_env = create_env(now_env);
	myvars->pwd = find_path(myvars->my_env, "PWD=");
	myvars->old_pwd = find_path(myvars->my_env, "OLDPWD=");
	myvars->home = find_path(myvars->my_env, "HOME=");
	myvars->stat = 0;
	myvars->hdoc = NULL;
	myvars->pipe_hdoc = NULL;
	if (!*envp)
		free_matrix(now_env);
	change_ucmd(&myvars->my_env, &myvars->export_env);
	return (myvars);
}
