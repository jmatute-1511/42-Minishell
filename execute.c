/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:09:48 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/04 18:31:22 by jmatute-         ###   ########.fr       */
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
	int h;
	char *buf;
	
	j = 0;
	if (it != 0)
		dup2(pipe[it - 1].fd[READ_P], STDIN_FILENO);
	if (it < n_childs - 1)
		dup2(pipe[it].fd[WRITE_P], STDOUT_FILENO);
	if (node->input != NULL || node->output != NULL)
		redirect_switch(node);
	while (j < n_childs - 1)
	{
		close(pipe[j].fd[WRITE_P]);
		close(pipe[j].fd[READ_P]);
		j++;
	}
	
}
void son_shell_execute(t_cmd_line *node, t_myvars *my_vars)
{
	char *path;
	char *quotes;
	char *expand;

	path = find_path_exec(node->first_arg, &my_vars->my_env);
	expand = expand_str(my_vars->my_env,node->arguments);
	quotes = set_quotes(expand);

	if (select_built(&node, &my_vars))
		exit(0);
	else
		execve(path, ft_split(quotes, ' '), my_vars->m_envp);
}

void close_pipes(t_pipes *child_pipe, int n_childs, pid_t *pids)
{
	int it;
	int status;
	
	it = 0;
	status = 0;
	while (it < n_childs)
	{
		if (it < n_childs - 1)
		{
			close(child_pipe[it].fd[WRITE_P]);
			close(child_pipe[it].fd[READ_P]);
		}
		waitpid(pids[it], &status, 0);
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
int execute_cmds(t_cmd_line **nodes, t_myvars *my_vars)
{
	int		it;
	int 	n_childs;
	t_pipes *child_pipe;
	pid_t	*pids;
	
	it = 0;
	n_childs = size_of_lst(nodes);
	pids = (pid_t *)malloc(sizeof(pid_t) * n_childs);
	child_pipe = create_pipes(n_childs);
	if (n_childs == 1 && (*nodes)->arguments)
	{
		if (select_built(nodes, &my_vars))
			return(0);
	}
	while(it < n_childs)
	{
		pids[it] = fork();
		if (pids[it] == 0)
		{
			g_proc = pids[it];
			if (error_cmd(nodes,&my_vars->my_env))
				exit(0);
			son_shell_pipes(child_pipe, it, n_childs, *nodes);
			if ((*nodes)->arguments != NULL)
				son_shell_execute(*nodes, my_vars);
			else
				exit(0);
		}
		(*nodes) = (*nodes)->next;
		it++;
	}
	close_pipes(child_pipe, n_childs, pids);
	return (0);
}