/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:09:48 by jmatute-          #+#    #+#             */
/*   Updated: 2022/06/24 19:48:52 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_pipes *new_pipe()
{
	t_pipes *pipe;

	pipe = malloc(sizeof(t_pipes));
	pipe->next = NULL;
	pipe->prev = NULL;
	return (pipe);
}

void 	add_back_pipe(t_pipes **lst, t_pipes **pipes)
{
	t_pipes *aux;

	
	if((*lst) != NULL)
	{
		aux = (*lst);
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = (*pipes);
		(*pipes)->next = NULL;
		(*pipes)->prev = aux;
	}
	else
	{
		(*lst) = (*pipes);
		(*pipes)->next = NULL;
		(*pipes)->prev = NULL;
	}
}

int size_of_lst(t_cmd_line **lst)
{
	int a;
	t_cmd_line *aux;

	a = 0;
	aux = (*lst);
	while(aux)
	{
		aux = aux->next;
		a++;
	}
	return(a);
}

char *find_path_exec(char *str, t_enviroment ** my_env)
{
	char	**split;
	char	*path;

	split = routes_of_path(my_env);
	path = access_cmd(split, str);
	return (path); 
}

void son_shell_first(t_cmd_line **cmd,t_pipes **pipes, t_myvars **my_vars)
{
	char *path;
	pid_t pid;

	pid = fork();
	if(pid == 0)
	{
		path = find_path_exec((*cmd)->first_arg, &(*my_vars)->my_env);
		close((*pipes)->fd[READ_P]);
		close(STDOUT_FILENO);
		dup2((*pipes)->fd[WRITE_P], STDOUT_FILENO);
		close((*pipes)->fd[WRITE_P]);
		if (select_built(cmd, (*my_vars)) == 0)
			execve(path,ft_split((*cmd)->arguments, ' '), (*my_vars)->m_envp);
	}
}

void son_shell_med(t_cmd_line **cmd,t_pipes **pipes, t_myvars **my_vars)
{
	char *path;
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		path = find_path_exec((*cmd)->first_arg, &(*my_vars)->my_env);
		close((*pipes)->fd[READ_P]);
		dup2((*pipes)->prev->fd[READ_P], STDIN_FILENO);
		close((*pipes)->prev->fd[READ_P]);
		dup2((*pipes)->fd[WRITE_P], STDOUT_FILENO);
		close((*pipes)->fd[WRITE_P]);
		if (select_built(cmd, (*my_vars)) == 0)
			execve(path, ft_split((*cmd)->arguments, ' '), (*my_vars)->m_envp);
	}
				
}

void son_shell_last(t_cmd_line **cmd,t_pipes **pipes, t_myvars **my_vars)
{
	char *path;
	pid_t pid;
	int a;

	pid = fork();
	a = 0;
	if (pid == 0)
	{
		path = find_path_exec((*cmd)->first_arg, &(*my_vars)->my_env);
		close((*pipes)->fd[WRITE_P]);
		dup2((*pipes)->fd[READ_P], STDIN_FILENO);
		close((*pipes)->fd[READ_P]);
		write(1, "ENTRE", 5);		
		a = execve(path, ft_split((*cmd)->arguments, ' '), (*my_vars)->m_envp);
	}
}

void one_cmd(t_cmd_line **cmds, t_myvars **my_vars)
{
	char *path;
	
	path = find_path_exec((*cmds)->first_arg, &(*my_vars)->my_env);
	if (select_built(cmds,(*my_vars)) == 0)
			execve(path, ft_split((*cmds)->arguments, ' '), (*my_vars)->m_envp);
}
void close_pipes(t_pipes **node, int it, int n_childs)
{
	if(it == 1 && it < (n_childs - 1))
		close((*node)->prev->fd[WRITE_P]);
	else if (it > 1 && it < (n_childs - 1))
	{
		close((*node)->prev->prev->fd[READ_P]);
		close((*node)->prev->fd[WRITE_P]);
	}
}
int execute_cmds(t_cmd_line **cmds, t_myvars **my_vars)
{
	int			status;
	int			aux;
	int			n_childs;
	pid_t		pid;	
	t_cmd_line	*node;
	t_pipes		*n_pipe;
	t_pipes		*pipes;

	aux = 0;
	pipes = NULL;
	n_childs = size_of_lst(cmds);
	if (n_childs == 1)
		one_cmd(cmds, my_vars);
	else
	{
		node =  (*cmds);
		while (aux < n_childs)
		{
			if (aux < (n_childs - 1))
			{
				n_pipe = new_pipe();
				pipe(n_pipe->fd);
				add_back_pipe(&pipes, &n_pipe);
			}
			//close_pipes(&n_pipe, aux, n_childs);
			if (aux == 0)
				son_shell_first(&node,&n_pipe, my_vars);
			else if (aux > 0 && aux < n_childs - 1)
				son_shell_med(&node,&n_pipe,  my_vars);
			else if (aux == (n_childs - 1))
				son_shell_last(&node,&n_pipe,my_vars);
			node = node->next;
			aux++;
		}
		wait(NULL);
	}
	return (0);
}