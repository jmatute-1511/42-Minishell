/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:59:01 by bremesar          #+#    #+#             */
/*   Updated: 2022/07/13 15:48:02 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_input(t_cmd_line *node)
{
	int		reader;
	char	*input;

	reader = 0;
	if (node->input != NULL)
	{
		while (node->input[reader])
		{
			if (node->input[reader] == '<' && node->input[reader + 1] != '<')
			{
				input = ft_strldup(&node->input[reader + 1],
						ft_point_strchr(&node->input[reader + 1], ' '));
				redirect_input(input);
			}
			if (node->input[reader] == '<' && node->input[reader + 1] == '<')
			{
				input = ft_strldup(&node->input[reader + 2],
						ft_point_strchr(&node->input[reader + 2], ' '));
				heredoc_initializer(input);
				reader++;
			}
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

void	redirect_switch(t_cmd_line *node)
{
	handle_input(node);
	handle_output(node);
}
