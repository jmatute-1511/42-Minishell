/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:46:48 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/09 17:33:49 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc,char **argv,char **envp)
{
    t_myvars myvars;
    char    *str;

    start_vars(&myvars,envp);
    if (!myvars.my_env)
        return(0);
    while (1)
    {
        str = readline("🧠🧠🧠Myshell🧠🧠🧠\n");
        parse_cmd(str);
        if (strcmp(str,"exit") == 0)
            break;
    }
}