/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_vars2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bremesar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:47:33 by bremesar          #+#    #+#             */
/*   Updated: 2022/07/25 17:47:35 by bremesar         ###   ########.fr       */
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
	my_envp[1] = ft_strdup("SHLVL=1");
	my_envp[2] = ft_strdup("_=/usr/bin/env");
	my_envp[3] = NULL;
	return (my_envp);
}
