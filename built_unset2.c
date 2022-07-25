/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bremesar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:30:29 by bremesar          #+#    #+#             */
/*   Updated: 2022/07/25 17:30:32 by bremesar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**parse_str_unset(char *str)
{
	char	*str_aux;
	char	**split;
	char	*aux;
	int		a;

	a = 0;
	str_aux = ft_strtrim(str, " ");
	split = ft_split(&str_aux[ft_point_strchr(str_aux, ' ')], ' ');
	while (split[a])
	{
		aux = set_quotes(split[a]);
		free(split[a]);
		split[a] = ft_strjoin(aux, "=");
		free(aux);
		a++;
	}
	free(str_aux);
	return (split);
}
