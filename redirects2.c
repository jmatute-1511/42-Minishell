/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:59:01 by bremesar          #+#    #+#             */
/*   Updated: 2022/07/24 21:42:29 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	continue_handle_hdoc(t_cmd_line *node, int *reader, t_myvars **my_vars)
{
	int		quote;
	char	*input;

	quote = 0;
	if (node->input[*reader] == '<' && node->input[*reader + 1] == '<')
	{
		if (node->input[(*reader) + 2] == '"' || \
		node->input[(*reader) + 2] == '\'')
			quote = 1;
		input = ft_strldup(&node->input[(*reader) + 2],
				ft_point_strchr(&node->input[(*reader) + 2], ' '));
		heredoc_initializer(input, my_vars, quote);
		(*reader)++;
	}
}

void	handle_heredoc(t_cmd_line *node, t_myvars **my_vars)
{
	int		reader;
	int		flag[2];

	reader = 0;
	flag[S_QUOTE] = 0;
	flag[P_QUOTE] = 0;
	while (node->input[reader])
	{
		if (flag[S_QUOTE] == 0 && flag[P_QUOTE] == 0)
			continue_handle_hdoc(node, &reader, my_vars);
		check_quotes(node->input[reader], &flag[P_QUOTE], &flag[S_QUOTE]);
		reader++;
	}
}

void	continue_handle_input(t_cmd_line *node, int *reader, t_myvars **my_vars)
{
	char	*input;

	input = NULL;
	if (node->input[(*reader)] == '<' && node->input[(*reader) + 1] != '<')
	{
		input = ft_strldup(&node->input[(*reader) + 1],
				ft_point_strchr(&node->input[(*reader) + 1], ' '));
		redirect_input(input);
	}
	if (node->input[(*reader)] == '<' && node->input[(*reader) + 1] == '<')
	{	
		heredoc_finish(my_vars);
		(*reader)++;
	}
}

void	handle_input(t_cmd_line *node, t_myvars **my_vars)
{
	int		reader;
	int		flag[2];

	reader = 0;
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;
	if (node->input != NULL)
	{
		while (node->input[reader])
		{
			if (flag[S_QUOTE] == 0 && flag[P_QUOTE] == 0)
				continue_handle_input(node, &reader, my_vars);
			check_quotes(node->input[reader], &flag[P_QUOTE], &flag[S_QUOTE]);
			reader++;
		}
	}
}

void	handle_output(t_cmd_line *node)
{
	int		reader;
	char	*output;

	reader = 0;
	if (node->output == NULL)
		return ;
	while (node->output[reader])
	{
		if (node->output[reader] == '>' && node->output[reader + 1] != '>')
		{
			output = ft_strldup(&node->output[reader + 1],
					ft_point_strchr(&node->output[reader + 1], ' '));
			redirect_output(output);
		}
		if (node->output[reader] == '>' && node->output[reader + 1] == '>')
		{
			output = ft_strldup(&node->output[reader + 2],
					ft_point_strchr(&node->output[reader + 2], ' '));
			redirect_output_double(output);
			reader++;
		}
		reader++;
	}
}
