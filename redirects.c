/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:43:58 by bremesar          #+#    #+#             */
/*   Updated: 2022/07/21 18:15:54 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_finish(t_myvars **my_vars)
{
	if ((*my_vars)->pipe_hdoc != NULL)
		dup2((*my_vars)->pipe_hdoc->fd[READ_P], STDIN_FILENO);	
}
void	heredoc_initializer(char *text, t_myvars **my_vars)
{
	char	*str;
	char	*join_str;
	char	*aux_str;

	join_str = NULL;
	while (1)
	{
		str = readline(YEL">"COLOR_RESET);
		if (ft_strcmp(str, text) == 0)
		{
			aux_str = join_str;
			join_str = ft_strjoin(aux_str, "\n");
			free(aux_str);
			free(str);
			free(text);
			break;
		}
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
