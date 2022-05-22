/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 20:38:50 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/22 11:45:19 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char *parse_str_unset(char *str)
{
    char *str_aux;
    char *str_aux2;
    char *str_aux3;
    

    str_aux = ft_strtrim(str, " ");
    str_aux2 = ft_strldup(str, ft_point_strchr(str, ' '));
    str_aux3 = ft_strjoin(str_aux2, "=");
    free(str_aux);
    free(str_aux2);
    return(str_aux3);
}
void unset_export_env(t_enviroment **export_env, t_enviroment **aux_export,  \
t_enviroment **prev_aux)
{
     if((*prev_aux) == NULL)
    {
        (*export_env) = (*export_env)->next;
        free((*aux_export));
    }
    else
    {
        (*prev_aux)->next = (*aux_export)->next;
        free((*aux_export));
    }
}

void    unset_myenv(t_enviroment **myenv ,t_enviroment  **aux_myenv, \
t_enviroment **prev_aux)
{
    if((*prev_aux) == NULL)
    {
        (*myenv) = (*myenv)->next;
        free((*aux_myenv));
    }
    else
    {
        (*prev_aux)->next = (*aux_myenv)->next;
        free((*aux_myenv));
    }
    
}

void buil_unset(t_enviroment **myenv, t_enviroment **export_env, char *str)
{
    t_enviroment    *aux_myenv;
    t_enviroment    *prev_aux;
    t_enviroment    *aux_export;
    char            *str_aux;

    aux_myenv = (*myenv);
    aux_export = (*export_env);
    str_aux = parse_str_unset(str);
    prev_aux = NULL;
    while (aux_myenv)
    {
        if(ft_strncmp(aux_myenv->env_var, str_aux, ft_point_strchr(str_aux, '=') ) == 0)
            unset_myenv(myenv,&aux_myenv,&prev_aux);
        prev_aux = aux_myenv;
        aux_myenv = aux_myenv->next;
    }
    prev_aux = NULL;
    while (aux_export)
    {
        if(ft_strncmp(aux_export->env_var, str_aux,  ft_point_strchr(str_aux, '='))== 0)
            unset_export_env(export_env,&aux_export,&prev_aux);
        prev_aux = aux_export;
        aux_export = aux_export->next;
    }
    free(str_aux);
}