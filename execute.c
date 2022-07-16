/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:09:48 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/16 20:06:02 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char *find_path_exec(char *str, t_enviroment **my_env)
{
	char	**split;
	char	*path;

	split = routes_of_path(my_env);
	path = access_cmd(split, str);
	free_matrix(split);
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

void	shell_level(char **m_envp)
{
	int a;
	char	*new_level;
	int level;
	int point;
	
	a = 0;
	while(m_envp[a])
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

/*char *parsed_arg(t_cmd_line *node, t_myvars **my_vars)
{
	
}*/
void son_shell_execute(t_cmd_line *node, t_myvars **my_vars)
{
	char *path;
	char *quotes;
	char *f_quotes;
	char *expand;

	f_quotes = set_quotes(node->first_arg);
	path = find_path_exec(f_quotes, &(*my_vars)->my_env);;
	expand = expand_str(*my_vars,node->arguments);
	quotes = set_quotes(expand);
	(*my_vars)->m_envp = enviroment_matrix((*my_vars)->my_env);
	if(ft_strcmp(path, "./minishell") == 0 || ft_strcmp(path, "minishell") == 0)
		shell_level((*my_vars)->m_envp);
	if (node->arguments != NULL && error_cmd(&node) == 0)
	{
		if (cmd_not_found(&node, &(*my_vars)->my_env))
			exit(127);
		if (select_built(&node, my_vars))
			exit(0);
		else
			execve(path, ft_split(quotes, ' '), (*my_vars)->m_envp);
	}
	free(path);
	free(expand);
	free(quotes);
	free(f_quotes);
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
	error_cmd(node);
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
	t_cmd_line *aux;
	
	pids = (pid_t *)malloc(sizeof(pid_t) * n_childs);
	child_pipe = create_pipes(n_childs);
	aux = (*nodes);
	while(*it < n_childs)
	{
		if ((*nodes)->input != NULL)
			handle_heredoc((*nodes));
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
	free(pids);
	free(child_pipe);
	free_cmds(&aux);
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