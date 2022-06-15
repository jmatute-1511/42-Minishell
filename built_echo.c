/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:55:32 by jmatute-          #+#    #+#             */
/*   Updated: 2022/06/15 19:22:21 by jmatute-         ###   ########.fr       */
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

void    built_echo(t_cmd_line **node)
{
	int		begin;
	int		new_begin;
	char	*echo;

	if (ft_strncmp((*node)->arguments, "echo",(ft_strlen("echo"))) == 0)
	{
		begin = ft_point_strchr((*node)->arguments, ' ');
		new_begin = after_option((*node)->arguments, "-n");
		if(new_begin > 0)
		{
			echo = ft_strtrim(&(*node)->arguments[new_begin], " ");
			if (echo != NULL)
			{
				printf("%s", echo);
				free(echo);
			}
		}
		else
		{
			echo = ft_strtrim(&(*node)->arguments[begin], " ");
			if (echo != NULL)
			{
				printf("%s\n", echo);
				free(echo);
			}
		}
	}
	
}