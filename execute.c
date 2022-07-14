/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:09:48 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/14 12:36:43 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char *find_path_exec(char *str, t_enviroment **my_env)
{
	char	**split;
	char	*path;

	split = routes_of_path(my_env);
	path = access_cmd(split, str);
	return (path); 
}

void 	son_shell_pipes(t_pipes *pipe, int it, int n_childs, t_cmd_line *node)
{
	int j;
	
	j = 0;
	if (node->input != NULL)
		handle_input(node);
	else if (it != 0)
		dup2(pipe[it - 1].fd[READ_P], STDIN_FILENO);
	if (node->output != NULL)
		handle_output(node);
	else if (it < n_childs - 1)
		dup2(pipe[it].fd[WRITE_P], STDOUT_FILENO);
	while (j < n_childs - 1)
	{
		close(pipe[j].fd[WRITE_P]);
		close(pipe[j].fd[READ_P]);
		j++;
	}
}

void son_shell_execute(t_cmd_line *node, t_myvars **my_vars)
{
	char *path;
	char *quotes;
	char *expand;

	path = NULL;
	expand = NULL;
	quotes = NULL;
	if (node->arguments != NULL && error_cmd(&node,my_vars) == 0)
	{
		quotes = set_quotes(node->first_arg);
		path = find_path_exec(quotes, &(*my_vars)->my_env);
		free(quotes);
		expand = expand_str(*my_vars,node->arguments);
		quotes = set_quotes(expand);
		if (cmd_not_found(&node, &(*my_vars)->my_env))
			exit(127);
		if (select_built(&node, my_vars))
			exit(0);
		else
			execve(path, ft_split(quotes, ' '), (*my_vars)->m_envp);
		free(quotes);
		free(expand);
		free(path);
	}
	else
		exit(0);
}

void close_pipes(t_pipes *child_pipe, int n_childs, pid_t *pids, t_myvars **my_vars)
{
	int it;
	int status;
	
	it = 0;
	status = 0;
	while (it < n_childs - 1)
	{
		close(child_pipe[it].fd[WRITE_P]);
		close(child_pipe[it].fd[READ_P]);
		it++;
	}
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

t_pipes *create_pipes(int n_childs)
{
	int it;
	t_pipes *pipes;
	
	it  = 0;
	pipes = (t_pipes *)malloc(sizeof(t_pipes) * n_childs - 1);
	while(it < n_childs - 1 && n_childs > 1)
	{
		pipe(pipes[it].fd);
		it++;
	}
	return(pipes);
}


void one_child_built(t_cmd_line **node, t_myvars **my_vars, int *it)
{
	int aux_out;
	int aux_in;
	
	aux_out = dup(STDOUT_FILENO);
	aux_in = dup(STDIN_FILENO);
	if ((*node)->input || (*node)->output)
		redirect_switch((*node));
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

void create_process(t_cmd_line **nodes, t_myvars **my_vars, int n_childs, int *it)
{
	t_pipes *child_pipe;
	pid_t	*pids;
	
	pids = (pid_t *)malloc(sizeof(pid_t) * n_childs);
	child_pipe = create_pipes(n_childs);
	while(*it < n_childs)
	{
		pids[(*it)] = fork();
		g_proc = pids[(*it)];
		if (pids[(*it)] == 0)
		{
			son_shell_pipes(child_pipe, (*it), n_childs, *nodes);
			son_shell_execute(*nodes, my_vars);
		}
		(*nodes) = (*nodes)->next;
		(*it)++;
	}
	close_pipes(child_pipe, n_childs, pids, my_vars);
}

int execute_cmds(t_cmd_line **nodes, t_myvars **my_vars)
{
	int 	n_childs;
	int		it;

	it = 0;
	n_childs = size_of_lst(nodes);
	if ((*nodes)->arguments  && bolean_built(nodes))
		one_child_built(nodes, my_vars, &it);
	create_process(nodes, my_vars, n_childs, &it);
	return (0);
}