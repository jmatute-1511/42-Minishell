/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:36:44 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/04 17:59:49 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void built_get_pwd(void)
{
    char *current;

    current = getcwd(NULL, 0);
    if (current != NULL)
        printf("%s   \n",current);
}