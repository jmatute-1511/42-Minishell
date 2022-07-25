/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:43:58 by bremesar          #+#    #+#             */
/*   Updated: 2022/07/25 17:06:50 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_finish(t_myvars **my_vars)
{
	if ((*my_vars)->pipe_hdoc != NULL)
		dup2((*my_vars)->pipe_hdoc->fd[READ_P], STDIN_FILENO);
}

int	exit_bucle_hdoc(char **join_str, char *str, char *quotes)
{
	char	*aux_str;

	if (ft_strcmp(str, quotes) == 0)
	{
		aux_str = (*join_str);
		(*join_str) = ft_strjoin(aux_str, "\n");
		free(aux_str);
		free(str);
		str = NULL;
		return (1);
	}
	return (0);
}

void	join_strings_hdoc(char **join_str, char	*str, int flag, \
t_myvars **my_vars)
{
	char	*expand;
	char	*aux_str;

	if ((*join_str) == NULL)
	{
		if (flag == 1)
			(*join_str) = ft_strdup(str);
		else
			(*join_str) = expand_str((*my_vars), str);
	}
	else
	{
		aux_str = (*join_str);
		if (flag == 1)
			(*join_str) = ft_strnjoin(3, aux_str, "\n", str);
		else
		{
			expand = expand_str((*my_vars), str);
			(*join_str) = ft_strnjoin(3, aux_str, "\n", expand);
			free(expand);
		}
		free(aux_str);
	}
}

void	heredoc_initializer(char *text, t_myvars **my_vars, int flag)
{
	char	*str;
	char	*join_str;
	char	*quotes;

	join_str = NULL;
	quotes = set_quotes(text);
	free(text);
	while (1)
	{
		str = readline(YEL">"COLOR_RESET);
		if (str == NULL)
		{
			free(join_str);
			exit(0);
		}
		if (exit_bucle_hdoc(&join_str, str, quotes))
			break ;
		else
			join_strings_hdoc(&join_str, str, flag, my_vars);
		free(str);
	}
	(*my_vars)->hdoc = join_str;
}

void	redirect_input(char *file)
{
	int		filedesc;
	char	*str;

	str = ft_strjoin("./", file);
	filedesc = open(str, O_RDONLY);
	if (filedesc < 0)
	{
		perror("open");
		return ;
	}
	dup2(filedesc, STDIN_FILENO);
	close(filedesc);
}
