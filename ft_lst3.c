/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:42:05 by jmatute-          #+#    #+#             */
/*   Updated: 2022/06/01 14:48:03 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_lst_cmds(t_cmd_line **lst)
{
    while ((*lst))
    {
        if ((*lst)->input)
            free((*lst)->input);
        if((*lst)->output)
            free((*lst)->output);
        if((*lst)->first_arg)
            free((*lst)->first_arg);
        if((*lst)->arguments)
            free((*lst)->arguments);
        if((*lst)->raw_cmd)
            free((*lst)->raw_cmd);
        (*lst) = (*lst)->next;
    }
}