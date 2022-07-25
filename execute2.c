/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bremesar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:36:25 by bremesar          #+#    #+#             */
/*   Updated: 2022/07/25 17:36:26 by bremesar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_hdoc_fd(t_myvars **my_vars)
{
	if ((*my_vars)->pipe_hdoc != NULL)
	{
		close((*my_vars)->pipe_hdoc->fd[READ_P]);
		close((*my_vars)->pipe_hdoc->fd[WRITE_P]);
		free((*my_vars)->pipe_hdoc);
		(*my_vars)->pipe_hdoc = NULL;
	}
}

void	close_pipes(t_pipes *child_pipe, int n_childs, pid_t *pids, \
t_myvars **my_vars)
{
	int	it;
	int	status;

	it = 0;
	status = 0;
	while (it < n_childs - 1)
	{
		close(child_pipe[it].fd[WRITE_P]);
		close(child_pipe[it].fd[READ_P]);
		it++;
	}
	close_hdoc_fd(my_vars);
	it = 0;
	while (it < n_childs)
	{
		waitpid(pids[it], &status, 0);
		if (WIFEXITED(status))
			(*my_vars)->stat = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			(*my_vars)->stat = 130;
		else if (status == 32512)
			(*my_vars)->stat = 127;
		it++;
	}
}

t_pipes	*create_pipes(int n_childs)
{
	int		it;
	t_pipes	*pipes;

	it = 0;
	pipes = (t_pipes *)malloc(sizeof(t_pipes) * n_childs - 1);
	while (it < n_childs - 1 && n_childs > 1)
	{
		pipe(pipes[it].fd);
		it++;
	}
	return (pipes);
}

void	create_hdocs(t_cmd_line *aux, t_myvars **my_vars)
{
	while (aux)
	{
		if (aux->input != NULL)
			handle_heredoc(aux, my_vars);
		aux = aux->next;
	}
}

void	signal_handler_son(int signum)
{
	if (signum == SIGINT)
		exit(0);
}
