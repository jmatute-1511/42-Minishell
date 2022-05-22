/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 12:14:18 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/22 16:47:23 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_chr(char c)
{
	if (c == ' ' || c == '$' || c == '\'' || c == '"')
		return (1);
	return (0);
}

int ft_point_strstr(char *str)
{
    
    int count_str;

    count_str = 0;
    while(str[count_str])
    {
        if (check_chr(str[count_str]))
            return(count_str);
        count_str++;   
    }
    return (count_str);
}