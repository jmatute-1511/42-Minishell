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

static int  after_string(char *str, char *find)
{
    int	after;
    int	begin;

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

static int  check_quote(char *str)
{
    int quote;
    int count;

    quote = 0;
    count = 0;
     while (str[count])
    {
        if (str[count] == '"')
            quote++;
        count++;
    }
    return(quote);
}

static char    *print_str(char *str)
{
    char	*cpy;
    char	*aux;
    int		quote;

    quote = check_quote(str);
    if (quote % 2 == 0)
    {
        cpy = (char *)malloc(sizeof(char) * ((ft_strlen(str) - quote) + 1));
        aux = cpy;
        while (*str != '\0')
        {
            if (*str != '"')
            {
                *cpy = *str;
                cpy++;
            }
            str++;            
        }
        *cpy = '\0';
        return(aux);
    }
    free(cpy);
    return (NULL);
}

void    built_echo(char *str)
{
    int		begin;
    int		new_begin;;
    char	*echo;

    if (after_string(str, "echo"))
    {
        begin = after_string(str, "echo");
        new_begin = after_string(str, "-n");
        if(new_begin > 0)
        {
            echo = print_str(&str[new_begin]);
            if (echo != NULL)
                printf("%s", ft_strtrim(echo, " "));
        }
        else
        {
            echo = print_str(&str[begin]);
            if (echo != NULL)
            printf("%s\n", ft_strtrim(echo, " "));
        }
    }
}