/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:13:30 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/09 12:54:24 by jmatute-         ###   ########.fr       */
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
		new = ft_nodenew(str);
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

char	**enviroment_matrix(char **envp)
{
	char	**aux_envp;
	int		size;
	int		count;

    size = 0;
    count = 0;
    aux_envp = NULL;
    if (!*envp)
    {
        while(envp[size])
            size++;
        aux_envp = (char **)malloc(sizeof(char *) * size + 1);
        while (count < size)
        {
            aux_envp[count] = ft_strdup(envp[count]);
            count++;
        }
        aux_envp[count] = NULL;
    }
    return(aux_envp);
}
char **create_env_if_not_env()
{
    char **my_envp;

    my_envp = (char **)malloc(sizeof(char *) * 4);
    if (!my_envp)
        return(NULL);
    my_envp[0] = ft_strdup("PWD=/Users/jmatute-/Desktop/mini/minishell");
    my_envp[1] = ft_strdup("SHLVL=1");
    my_envp[2] = ft_strdup("_=/usr/bin/env");
    my_envp[3] = NULL;
    return(my_envp);
}

t_myvars	*start_vars(t_myvars *myvars, char **envp)
{
    char **my_envp;

    my_envp = NULL;
    if (!*envp)
    {
        my_envp = create_env_if_not_env();
        myvars = malloc(sizeof(t_myvars));
        myvars->first_pwd = getcwd(NULL, 0);
        myvars->export_env = create_export_env(my_envp);
        myvars->my_env = create_env(my_envp);
        myvars->m_envp = enviroment_matrix(my_envp);
        myvars->stat = 0;
    }
    else{
        myvars = malloc(sizeof(t_myvars));
        myvars->first_pwd = getcwd(NULL, 0);
        myvars->export_env = create_export_env(envp);
        myvars->my_env = create_env(envp);
        myvars->m_envp = enviroment_matrix(envp);
        myvars->stat = 0;
    }
    return(myvars);
}
