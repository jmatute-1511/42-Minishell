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

//usa el comando "bash" en la terminal para los ejemplos
//haz el de <<

void	redirect_switch(t_cmd_line *node)
{
	int		reader;
	char	*input;
	char	*output;

	if (node->input != NULL)
	{
		reader = 0;
		while (node->input[reader])
		{
			if (node->input[reader] == '<' && node->input[reader + 1] != '<')
			{
				input = ft_strldup(&node->input[reader + 1], ft_point_strchr(&node->input[reader + 1], ' '));
				redirect_input(input);
			}
			if (node->input[reader] == '<' && node->input[reader + 1] == '<')
			{
				input = ft_strldup(&node->input[reader + 2], ft_point_strchr(&node->input[reader + 2], ' '));
				heredoc_initializer(input);
				reader++;
			}
			reader++;
		}
	}
	reader = 0;
	if (node->output != NULL)
	{
		while (node->output[reader])
		{
			if (node->output[reader] == '>' && node->output[reader + 1] != '>')
			{
				output = ft_strldup(&node->output[reader + 1], ft_point_strchr(&node->output[reader + 1], ' '));
				redirect_output(output);
			}
			if (node->output[reader] == '>' && node->output[reader + 1] == '>')
			{
				output = ft_strldup(&node->output[reader + 2], ft_point_strchr(&node->output[reader + 2], ' '));
				redirect_output_double(output);
				reader++;
			}
			reader++;
		}
	}
}

void	heredoc_initializer(char *text)
{
	int		filedesc;
	int		out_aux; //pipe duplicado auxiliar
	char	*str;
	char 	*join_str;
	char 	*aux_str;

	join_str = NULL;
	while (1)
	{
		str = readline(ROJO_T">"COLOR_RESET);
		if (ft_strcmp(str, text) == 0)
		{
			aux_str = join_str;
			join_str = ft_strjoin(aux_str, "\n");
			free(aux_str);
			filedesc = open("temp", O_WRONLY | O_TRUNC | O_CREAT);
				if (filedesc < 0)
					return ;
			write(filedesc, join_str, ft_strlen(join_str));
			close(filedesc);
			filedesc = open("temp", O_RDONLY);
			dup2(filedesc, STDIN_FILENO);
			close(filedesc);
			return;
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
		//cmd error
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
		//cmd error
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
		//cmd error
		perror("open");
		return ;
	}
	dup2(filedesc, STDOUT_FILENO);
	close(filedesc);
}