/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:09:48 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/24 21:58:27 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path_exec(char *str, t_enviroment **my_env)
{
	char	**split;
	char	*path;

	split = routes_of_path(my_env);
	path = access_cmd(split, str);
	if (split)
		free_matrix(split);
	return (path);
}

void	son_shell_pipes(t_pipes *pipe, int it, t_myvars **my_vars, \
t_cmd_line *node)
{
	int	j;

	j = 0;
	if (node->input != NULL)
		handle_input(node, my_vars);
	else if (it != 0)
		dup2(pipe[it - 1].fd[READ_P], STDIN_FILENO);
	if (node->output != NULL)
		handle_output(node);
	else if (it < (*my_vars)->n_childs - 1)
		dup2(pipe[it].fd[WRITE_P], STDOUT_FILENO);
	while (j < (*my_vars)->n_childs - 1)
	{
		close(pipe[j].fd[WRITE_P]);
		close(pipe[j].fd[READ_P]);
		j++;
	}
	if ((*my_vars)->pipe_hdoc)
	{
		close((*my_vars)->pipe_hdoc->fd[READ_P]);
		close((*my_vars)->pipe_hdoc->fd[WRITE_P]);
	}
}

void	shell_level(char **m_envp)
{
	int		a;
	char	*new_level;
	int		level;
	int		point;

	a = 0;
	while (m_envp[a])
	{
		point = ft_point_strchr(m_envp[a], '=');
		if (ft_strncmp(m_envp[a], "SHLVL=", point) == 0)
		{
			level = ft_atoi(&m_envp[a][point + 1]) + 1;
			free(m_envp[a]);
			new_level = ft_itoa(level);
			m_envp[a] = ft_strjoin("SHLVL=", new_level);
			free(new_level);
		}	
		a++;
	}
}

void	son_shell_execute(t_cmd_line *node, t_myvars **my_vars)
{
	char	*path;
	char	*quotes;
	char	*f_quotes;
	char	*expand;

	f_quotes = set_quotes(node->first_arg);
	expand = expand_str(*my_vars, node->arguments);
	quotes = set_quotes(expand);
	(*my_vars)->m_envp = enviroment_matrix((*my_vars)->my_env);
	if (node->arguments != NULL && error_cmd(&node) == 0)
	{
		if (select_built(&node, my_vars))
			exit(0);
		path = find_path_exec(f_quotes, &(*my_vars)->my_env);
		if (ft_strcmp(path, "./minishell") == 0 || \
		ft_strcmp(path, "minishell") == 0)
			shell_level((*my_vars)->m_envp);
		execve(path, ft_split(quotes, ' '), (*my_vars)->m_envp);
	}
	exit(0);
}

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

void signal_handler_son(int signum)
{
	if (signum == SIGINT)
		exit(0);
}
void	loop_hdoc(t_cmd_line **nodes, t_myvars **my_vars)
{
	t_cmd_line	*aux;
	pid_t		pid;

	aux = (*nodes);
	(*my_vars)->pipe_hdoc = malloc(sizeof(t_pipes) * 1);
	pipe((*my_vars)->pipe_hdoc->fd);
	pid= fork();
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
