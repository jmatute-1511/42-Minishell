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

static void change_location(t_enviroment **env_var, t_enviroment **old_var, char *str, char *actual)
{
    char    *current;

    
    chdir(str);
    current = getcwd(NULL, 0);
    if ((*env_var))
    {
        free((*env_var)->env_var);
        (*env_var)->env_var = ft_strjoin ("PWD=", current);
    }
    if ((*old_var))
    {
        free((*old_var)->env_var);
        (*old_var)->env_var = ft_strjoin("OLDPWD=",actual);
    }
}

void built_cd(t_myvars **myvars,char *str)
{
    t_enviroment	*pwd;
    int				point;
	char			*trim;
    t_enviroment    *old_pwd;
    char            *actual;
    
	point = ft_point_strchr(str, ' ');
	trim = ft_strtrim(&str[point], " ");
    actual = getcwd(NULL,0);
    if (access(trim, X_OK) != 0 || (*myvars)->my_env == NULL)
        return ;
    pwd = find_path(*myvars, "PWD=");
    old_pwd = find_path(*myvars, "OLDPWD=");
    change_location(&pwd, &old_pwd, trim, actual);
}