/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:11:49 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/15 23:41:39 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_matrixlen(char **matrix)
{
    int a;
     
    a = 0;
    while(matrix[a]  != NULL)
        a++;
    return (a);
}

void built_exit(char *str, t_myvars **my_vars)
{
    int it;
    char *str_m;
    char **matrix; 
    char *err_msg;
    int n_atoi;

    it = 0;
    (void)my_vars;
    matrix = ft_split(str, ' ');
    str_m = matrix[1];
    if (ft_matrixlen(matrix) > 2)
    {
        ft_putstr_fd("Myshell :exit: too many arguments", 2);
        exit(1);
    }
    else if (str_m == NULL)
        exit(EXIT_SUCCESS);
    if (str_m[it] == '-')
        it++;
    while (str_m[it] >= '0' && str_m[it] <= '9' && str_m)
        it++;
    if (str_m[it] != '\0' || it > 19)
    {
        err_msg = ft_strnjoin(3, "exit: ", str_m, ": numeric argument required\n");
        ft_putstr_fd(err_msg, 2);
        exit(255);
    }
    n_atoi = ft_atoi(str_m);
    if (n_atoi >= 256)
        (*my_vars)->stat = n_atoi % 256;
    else
        (*my_vars)->stat = n_atoi;
    if (n_atoi < 0)
        exit(UCHAR_MAX - (*my_vars)->stat + 1);
    exit((*my_vars)->stat);
}