/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:42:58 by jmatute-          #+#    #+#             */
/*   Updated: 2021/06/01 12:19:32 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t		count;
	char		*cpy_s;

	cpy_s = (char *)s;
	count = 0;
	while (count <= ft_strlen(s))
	{
		if (cpy_s[count] == (char)c)
			return ((char *)s + count);
		count++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (0);
}
