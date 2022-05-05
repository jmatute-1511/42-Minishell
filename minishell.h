/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:23:12 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/05 22:51:08 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
 #define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <sys/types.h>

typedef struct s_myvars
{
    char    *first_pwd;
    char    **enviroment;
    char    **old_enviroment;

}               t_myvars;

void    start_vars(t_myvars *myvars, char **envp) ;
void    built_get_pwd(void);
void    built_echo(char *str);
void    open_directory(char *str);
void    built_cd(t_myvars *myvars,char *str);

#endif