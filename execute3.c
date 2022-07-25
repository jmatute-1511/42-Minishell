/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bremesar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:36:36 by bremesar          #+#    #+#             */
/*   Updated: 2022/07/25 17:36:39 by bremesar         ###   ########.fr       */
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
