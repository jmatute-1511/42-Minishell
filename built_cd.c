 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:53:55 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/08 13:38:54 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_enviroment 	*find_path(t_myvars *myvars, char *str)
{
    t_enviroment *aux;
    
    aux = myvars->my_env;
    while (aux->next)
    {
        if(ft_strncmp(aux->env_var, str, ft_strlen(str)) == 0)
            return(aux);
        aux = aux->next;
    }
    return (NULL);
}

static void change_location(t_enviroment **env_var, char *str)
{
    char    *current;
    char    *aux;

    chdir(str);
    current = getcwd(NULL, 0);
    aux = (*env_var)->env_var;
    (*env_var)->env_var = ft_strjoin ("PWD=", current);
    printf("%s\n",(*env_var)->env_var);
}

void built_cd(t_myvars *myvars,char *str)
{
    t_enviroment *pwd;

    if (access(str, X_OK) != 0 || myvars->my_env == NULL)
        return ;    
    pwd = find_path(myvars, "PWD=");
    if (ft_strncmp(pwd->env_var,"PWD=", ft_strlen("PWD=")) == 0)
        change_location(&pwd, str);
}