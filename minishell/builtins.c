/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:55:32 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/03 19:21:02 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int after_string(char *str, char *find)
{
    int after;
    int begin;

    after = 0;
    begin  = 0;
    while (str[after])
    {
        while (str[after] == find[begin])
        {
            after++;
            begin++;
        }
        if (begin == ft_strlen(find))
            return(after + 1);
        begin  = 0;
        after++;
    }
    return (0);
}

void    built_echo(char *str)
{
    int count;
    int begin;
    int flag;
    char **matrix;

    flag = 0;
    count = 0;
    if (after_string(str, "echo -n"))
    {
        begin = after_string(str, "echo -n");
        flag = 1;
    }
    else if (after_string(str, "echo"))
        begin = after_string(str, "echo");
    matrix = ft_split_ignore(&str[begin], ' ', '"');
    while (matrix[count])
    {
        if (matrix[count + 1] != NULL)
            printf("%s ",ft_strtrim(matrix[count], "\""));
        else if (flag == 1)
            printf("%s",ft_strtrim(matrix[count], "\""));
        else 
            printf("%s\n",ft_strtrim(matrix[count], "\""));
       // printf(" WORDS %d\n", count);
        count++;
    }
    free_matrix(matrix);
}