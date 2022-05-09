/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:55:32 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/09 16:57:04 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  after_string(char *str, char *find)
{
	int	after;
	int	begin;

	after = 0;
	begin  = 0;
	while (str[after])
	{
		while (str[after] == find[begin])
		{
			after++;
			begin++;
		}
		if (begin == ft_strlen(find))
			return(after + 1);
		begin  = 0;
		after++;
	}
	return (0);
}
static int parse_str(char *str)
{
	int count;
	int simple_quote;
	int pair_quote;

	pair_quote = 0;
	simple_quote = 0;
	count = 0;
	while (str[count])
	{
		if (str[count] == '"'  && pair_quote == 0 && simple_quote == 0)
			pair_quote++;
		else if (str[count] == '"'  && pair_quote == 1)
			pair_quote--;
		if (str[count] == '\''  && simple_quote == 0 && pair_quote == 0)
			simple_quote++;
		else if (str[count] == '\''  && simple_quote == 1)
			simple_quote--;
		count++;
	}
	if (pair_quote != 0  || simple_quote != 0)
		return (1);
	return (0);
}

static char    *print_str(char *str)
{
	char	*cpy;
	char	*aux;

	if(parse_str(str))
		return(NULL);
	cpy = (char *)malloc(sizeof(char) * ((ft_strlen(str)  + 1)));
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
	int		new_begin;;
	char	*echo;

	if (after_string(str, "echo"))
	{
		begin = after_string(str, "echo");
		new_begin = after_string(str, "-n");
		if(new_begin > 0)
		{
			echo = print_str(&str[new_begin]);
			if (echo != NULL)
				printf("%s", ft_strtrim(echo, " "));
		}
		else
		{
			echo = print_str(&str[begin]);
			if (echo != NULL)
			printf("%s\n", ft_strtrim(echo, " "));
		}
	}
}