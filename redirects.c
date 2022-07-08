/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bremesar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:43:58 by bremesar          #+#    #+#             */
/*   Updated: 2022/06/18 14:44:05 by bremesar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_finish(char *join_str)
{
	int		filedesc;
	char	*aux_str;

	aux_str = join_str;
	join_str = ft_strjoin(aux_str, "\n");
	free(aux_str);
	filedesc = open("temp", O_WRONLY | O_TRUNC | O_CREAT);
	write(filedesc, join_str, ft_strlen(join_str));
	close(filedesc);
	filedesc = open("temp", O_RDONLY);
	dup2(filedesc, STDIN_FILENO);
	close(filedesc);
}

void	heredoc_initializer(char *text)
{
	int		filedesc;
	int		out_aux;
	char	*str;
	char	*join_str;
	char	*aux_str;

	join_str = NULL;
	while (1)
	{
		str = readline(ROJO_T">"COLOR_RESET);
		if (ft_strcmp(str, text) == 0)
			return (heredoc_finish(join_str));
		else
		{
			if (join_str == NULL)
				join_str = ft_strdup(str);
			else
			{
				aux_str = join_str;
				join_str = ft_strnjoin(3, aux_str, "\n", str);
				free(aux_str);
			}
		}
	}
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

void	redirect_output(char *file)
{
	int		filedesc;
	char	*str;

	str = ft_strjoin("./", file);
	filedesc = open(str, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if (filedesc < 0)
	{
		perror("open");
		return ;
	}
	dup2(filedesc, STDOUT_FILENO);
	close(filedesc);
}

void	redirect_output_double(char *file)
{
	int		filedesc;
	char	*str;

	str = ft_strjoin("./", file);
	filedesc = open(str, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
	if (filedesc < 0)
	{
		perror("open");
		return ;
	}
	dup2(filedesc, STDOUT_FILENO);
	close(filedesc);
}
