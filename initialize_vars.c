/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:13:30 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/16 20:13:26 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_enviroment	*create_export_env(char **envp)
{
	t_enviroment	*export_env;
	t_enviroment	*new;
	char			*str;
	int				count;

	count = 0;
	export_env = NULL;
	if (envp == NULL)
		return (NULL);
	while (envp[count])
	{
		str = ft_strdup(envp[count]);
		if (ft_strncmp(envp[count], "SHLVL=", ft_point_strchr(envp[count], '=')) == 0)
			shell_level(&str);
		new = ft_nodenew(str);
		free(str);
		ft_nodeadd_alphabet(&export_env, &new);
		count++;
	}
	return (export_env);
}

t_enviroment	*create_env(char **envp)
{
	t_enviroment	*my_env;
	t_enviroment	*new;
	char			*str;
	int				count;

	count = 0;
	my_env = NULL;
	if (envp == NULL)
		return (NULL);
	while (envp[count])
	{
		str = ft_strdup(envp[count]);
		if (ft_strncmp(envp[count], "SHLVL=", ft_point_strchr(envp[count], '=')) == 0)
			shell_level(&str);
		new = ft_nodenew(str);
		ft_nodeadd_back(&my_env, &new);
		count++;
	}
	return (my_env);
}

int ft_env_size(t_enviroment *my_env)
{
	int a;

	a = 0;
	while(my_env)
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
	char 	**m_envp;

	it = 0;
	size = ft_env_size(my_env);
	m_envp = (char **)malloc(sizeof(char *) * size + 1);
	while(my_env)
	{
		m_envp[it] = ft_strdup(my_env->env_var);
		my_env = my_env->next;
		it++;
	}
	m_envp[it] = NULL;
	return(m_envp);
}
char	**create_env_if_not_env(void)
{
	char	**my_envp;

	my_envp = (char **)malloc(sizeof(char *) * 4);
	if (!my_envp)
		return (NULL);
	my_envp[0] = ft_strjoin("PWD=",getcwd(NULL, 0));
	my_envp[1] = ft_strdup("SHLVL=2");
	my_envp[2] = ft_strdup("_=/usr/bin/env");
	my_envp[3] = NULL;
	return (my_envp);
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
	myvars->old_pwd=find_path(myvars->my_env, "OLDPWD=");
	myvars->home =find_path(myvars->my_env,"HOME=");
	myvars->stat = 0;
	if(!*envp)
		free_matrix(now_env);
	return (myvars);
}
