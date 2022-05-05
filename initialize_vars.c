/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:13:30 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/05 22:58:38 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **fill_enviroment(char **envp)
{
    int len;
    int it;
    char **enviroment;

    len =  0;
    it = 0;
    if(*envp == NULL)
        return(NULL);
    while (envp[len])
        len++;
    enviroment = (char **)malloc(sizeof(char *) * len + 1);
    while (envp[it])
    {
        enviroment[it] = envp[it];
        it++;
    }
    enviroment[len] = NULL;
    return (enviroment);
}
char **set_enviroment(t_myvars *myvars, char *str)
{
}
void start_vars(t_myvars *myvars, char **envp)   
{
    myvars->first_pwd = getcwd(NULL, 0);
    myvars->enviroment = fill_enviroment(envp);
    
}