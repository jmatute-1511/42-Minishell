/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:13:30 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/12 20:47:35 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_enviroment *create_export_env(char **envp)
{
    t_enviroment	*export_env;
    t_enviroment    *new;
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
    myvars->export_env = create_export_env(envp);
    myvars->my_env = create_env(envp);
}