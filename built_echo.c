/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:55:32 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/11 16:54:32 by jmatute-         ###   ########.fr       */
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
			begin++;
			after++;
			while (str[after] == find[begin])
				after++;
			if (str[after] == ' ')
				return(after + 1);
			else 
				return (0);
		}
		after++;
	}
	return (0);
}

static char    *print_str(char *str)
{
	char	*cpy;
	char	*aux;
	char 	*aux2;

	aux2 = ft_strtrim(str, " ");
	if (ft_strlen(aux2) == 0)
	{		
		free(aux2);
		return(NULL);
	}
	cpy = (char *)malloc(sizeof(char) * ((ft_strlen(str)  + 1)));
	if(!cpy)
		return(NULL);
	aux = cpy;
	while (*str != '\0')
	{
		if (*str != '"')
		{
			*cpy = *str;
			cpy++;
		}
		str++;            
	}
	*cpy = '\0';
	return(aux);
}

void    built_echo(char *str)
{
	int		begin;
	int		new_begin;
	char	*echo;

	if (ft_strncmp(str, "echo",(ft_strlen("echo"))) == 0)
	{
		begin = ft_strlen("echo");
		new_begin = after_option(str, "-n");
		if(new_begin > 0)
		{
			echo = print_str(&str[new_begin]);
			if (echo != NULL)
				printf("%s", ft_strtrim(echo, " "));
		}
		else
		{
			echo = print_str(&str[begin + 1]);
			if (echo != NULL)
				printf("%s\n", ft_strtrim(echo, " "));
		}
	}
	
}