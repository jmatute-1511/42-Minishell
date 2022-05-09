/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:13:30 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/09 16:24:24 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_enviroment *create_env(char **envp)
{
    t_vars_env vars;
    
    vars.count = 0;
    vars.my_env = NULL;
    if (envp == NULL)
        return (NULL);
    while (envp[vars.count])
    {
        vars.str = ft_strdup(envp[vars.count]);
        ft_nodeadd_alphabet(&vars.my_env, ft_nodenew(vars.str));
		//alphabet_env(&vars, envp);
        vars.count++;
    }
    return (vars.my_env);
}

void start_vars(t_myvars *myvars,char **envp)   
{
    myvars->first_pwd = getcwd(NULL, 0);
    myvars->my_env = create_env(envp);
}