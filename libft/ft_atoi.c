/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 21:40:16 by jmatute-          #+#    #+#             */
/*   Updated: 2021/12/08 14:03:30 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	count;
	long	save;
	long	sign;
	int		neg;

	count = 0;
	save = 0;
	sign = 0;
	neg = 1;
	while ((str[count] >= 9 && str[count] <= 13) || str[count] == 32)
		count++;
	while ((str[count] == '-' || str[count] == '+'))
	{
		if (str[count] == '-')
			neg = -1;
		 (sign += 1) && (count += 1);
	}
	while (ft_isdigit(str[count]) && sign <= 1 && save <= 21474836479)
		save = save * 10 + (str[count++] - 48);
	save = save * neg;
	if (save > 2147483647)
		return (-1);
	if (save < -2147483648)
		return (0);
	return ((int)save);
}
