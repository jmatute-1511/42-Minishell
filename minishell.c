/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:46:48 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/05 22:44:42 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc,char **argv,char **envp)
{
    t_myvars myvars;
    int count;

    start_vars(&myvars,envp);
    count = 0;
   /* while (myvars.enviroment[count])
    {
        printf("%s\n",myvars.enviroment[count]);
        count++;
    }*/
    built_get_pwd();
    built_cd(&myvars,argv[1]);
    built_get_pwd();
}