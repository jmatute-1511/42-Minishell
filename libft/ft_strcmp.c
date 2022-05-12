/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:23:10 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/11 21:19:59 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	count;
	int		n;
	int		s;
	int 	l;

	count = 0;
	while ((s1[count] || s2[count]))
	{
		n = s1[count];
		s = s2[count];
		l = n - s;
		if (s1[count] != s2[count])
			return (l);
		count++;
	}
	return (0);
}
