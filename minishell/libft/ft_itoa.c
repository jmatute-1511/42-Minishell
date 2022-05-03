/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 09:49:47 by jmatute-          #+#    #+#             */
/*   Updated: 2021/05/30 19:54:03 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*save;
	int		digit;
	int		pass;
	int		cpy_n;

	digit = 0;
	pass = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
		(n = n * -1) && (digit += 1) && (pass += 1);
	cpy_n = n;
	while (cpy_n > 0)
		(digit += 1) && (cpy_n = cpy_n / 10);
	(save = malloc (digit + 1)) && (save[digit] = '\0');
	if (!save)
		return (NULL);
	while (n > 0 && (digit - 1) > 0)
		(save[digit - 1] = n % 10 + '0') && (digit--) && (n = n / 10);
	save[digit - 1] = n % 10 + '0';
	if (pass == 1)
		(save[digit - 1] = '-');
	return (save);
}
