/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:09:48 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/25 16:31:27 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_hdoc(t_cmd_line **nodes, t_myvars **my_vars)
{
	t_cmd_line	*aux;
	pid_t		pid;

	aux = (*nodes);
	(*my_vars)->pipe_hdoc = malloc(sizeof(t_pipes) * 1);
	pipe((*my_vars)->pipe_hdoc->fd);
	pid = fork();
	g_proc = pid;
	if (pid == 0)
	{
		signal(SIGINT, signal_handler_son);
		create_hdocs(aux, my_vars);
		if ((*my_vars)->hdoc != NULL)
		{
			ft_putstr_fd((*my_vars)->hdoc, (*my_vars)->pipe_hdoc->fd[WRITE_P]);
			free((*my_vars)->hdoc);
		}
		close((*my_vars)->pipe_hdoc->fd[READ_P]);
		close((*my_vars)->pipe_hdoc->fd[WRITE_P]);
		exit(0);
	}
	waitpid(pid, NULL, 0);
}

void	one_child_built(t_cmd_line **node, t_myvars **my_vars, int *it)
{
	int	aux_out;
	int	aux_in;

	error_cmd(node);
	loop_hdoc(node, my_vars);
	aux_in = dup(STDIN_FILENO);
	aux_out = dup(STDOUT_FILENO);
	if ((*node)->input)
		handle_input((*node), my_vars);
	if ((*node)->output)
		handle_output((*node));
	if (select_built(node, my_vars))
	{
		(*my_vars)->stat = 0;
		dup2(aux_out, STDOUT_FILENO);
		close(aux_out);
		dup2(aux_in, STDIN_FILENO);
		close(aux_in);
	}
	(*it)++;
}

void	free_elements(t_pipes *child_pipe, pid_t *pids, t_cmd_line **aux)
{
	free(pids);
	free(child_pipe);
	free_cmds(aux);
}

void	create_process(t_cmd_line **nodes, t_myvars **my_vars, \
int n_childs, int *it)
{
	t_pipes		*child_pipe;
	pid_t		*pids;
	t_cmd_line	*aux;

	pids = (pid_t *)malloc(sizeof(pid_t) * n_childs);
	child_pipe = create_pipes(n_childs);
	aux = (*nodes);
	loop_hdoc(nodes, my_vars);
	while (*it < n_childs)
	{	
		pids[(*it)] = fork();
		g_proc = pids[(*it)];
		if (pids[(*it)] == 0)
		{	
			if (cmd_not_found(nodes, &(*my_vars)->my_env))
				exit(127);
			son_shell_pipes(child_pipe, (*it), my_vars, *nodes);
			son_shell_execute(*nodes, my_vars);
		}
		(*nodes) = (*nodes)->next;
		(*it)++;
	}
	close_pipes(child_pipe, n_childs, pids, my_vars);
	free_elements(child_pipe, pids, &aux);
}

int	execute_cmds(t_cmd_line **nodes, t_myvars **my_vars)
{
	int	it;

	it = 0;
	(*my_vars)->n_childs = size_of_lst(nodes);
	if ((*nodes)->arguments && bolean_built(nodes) && (*my_vars)->n_childs == 1)
		one_child_built(nodes, my_vars, &it);
	else
		create_process(nodes, my_vars, (*my_vars)->n_childs, &it);
	return (0);
}
