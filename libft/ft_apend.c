/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apend.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 20:24:15 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/07 15:49:21 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char  **ft_apend(char *str_matrix, int nstrings,  ...)
{
	int len;
	char *str;
	char **matrix;
	char **aux_matrix;
	va_list strings;

	va_start(strings, nstrings);
	len = 0;
	while (str_matrix[len])
		len++;
	matrix = (char **)malloc(sizeof(char *) * (len + nstrings) + 1);
	len = 0;
	while (matrix[len])
	{
		if(aux_matrix[len])
			matrix[len] = aux_matrix[len];
		else
		{
			str = va_arg(strings, char *);
			matrix[len] = ft_strdup(str);
		}
		len++;
	}
	matrix[len] = NULL;
	va_end(strings);
	return (matrix);
}