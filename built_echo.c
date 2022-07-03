/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:55:32 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/03 16:35:28 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  after_option(char *str, char *find)
{
	int	after;
	int	begin;

	after = 0;
	begin  = 0;
	while (str[after])
	{
		if (str[after] == find[begin])
		{
			after++;
			begin++;
			while (str[after] == find[begin])
				after++;
			if (str[after] == ' ')
				return(after);
			else 
				return (0);
		}
		after++;
	}
	return (0);
}

void print_echo(char *str)
{
	char	**echo;
	char	*clean;
	int		a;
	
	a = 0;
	echo = ft_split_ignore(str, ' ', "\"'");
	while (echo[a])
	{
		clean = set_quotes(echo[a]);
		if (clean != NULL)
		{
			ft_putstr_fd(clean, 1);
			if (echo[a + 1] != NULL)
				write(1, " ", 1);				
			free(clean);
		}
		a++;
	}
	free_matrix(echo);
}

void    built_echo(char *str)
{
	int		begin;
	int		new_begin;
	char	*echo;

	begin = ft_point_strchr(str, ' ');
	new_begin = after_option(str, "-n");
	if(new_begin > 0)
		print_echo(&str[new_begin]);
	else
	{
		print_echo(&str[begin]);
		write(1, "\n", 1);
	}
}