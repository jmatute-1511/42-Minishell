/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:13:30 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/11 22:03:46 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_enviroment *create_export_env(char **envp)
{
    t_enviroment	*export_env;
    char			*str;
	int				count;
    
    count = 0;
    export_env = NULL;
    if (envp == NULL)
        return (NULL);
    while (envp[count])
    {
        str = ft_strdup(envp[count]);
        ft_nodeadd_alphabet(&export_env, ft_nodenew(str));
        count++;
    }
    return (export_env);
}
t_enviroment *create_env( char **envp)
{
    t_enviroment	*my_env;
    char			*str;
    int				count;
    
    count = 0;
    my_env  = NULL;
    if (envp == NULL)
        return (NULL);
    while (envp[count])
    {
        str = ft_strdup(envp[count]);
        ft_nodeadd_back(&my_env, ft_nodenew(str));
        count++;
    }
    return (my_env);
    
}
void start_vars(t_myvars *myvars,char **envp)   
{
    myvars->first_pwd = getcwd(NULL, 0);
    myvars->alphabet_env = create_export_env(envp);
    myvars->my_env = create_env(envp);
}