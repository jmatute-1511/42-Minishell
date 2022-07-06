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
	int reader;
	char *input;
	char *output;

	if (node->input != NULL)
	{
		reader = 0;
		while(node->input[reader])
		{
			if (node->input[reader] == '<' && node->input[reader + 1] != '<')
			{
				input = ft_strldup(&node->input[reader + 1], ft_point_strchr(&node->input[reader + 1], ' '));
				redirect_input(input);
			}
			reader++;
		}
	}

	reader = 0;
	if(node->output != NULL)
	{
		while(node->output[reader])
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

	filedesc = open("temp", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if (filedesc < 0)
		return ;
	out_aux = dup(1);
	while (1)
	{
		str = readline(ROJO_T">"COLOR_RESET);
		if (ft_strcmp(str, text) == 0)
		{
			dup2(out_aux, 1);
			close(filedesc);
			return;
		}
		else
		{
			dup2(filedesc, 1);
			printf("%s\n", str);
			dup2(out_aux, 1);
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