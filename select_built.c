/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:21:11 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/24 21:40:38 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bolean_built(t_cmd_line **node)
{
	if (strcmp((*node)->first_arg, "echo") == 0)
		return (1);
	else if (strcmp((*node)->first_arg, "cd") == 0)
		return (1);
	else if (strcmp((*node)->first_arg, "env") == 0)
		return (1);
	else if (strcmp((*node)->first_arg, "export") == 0)
		return (1);
	else if (strcmp((*node)->first_arg, "pwd") == 0)
		return (1);
	else if (strcmp((*node)->first_arg, "unset") == 0)
		return (1);
	else if (strcmp((*node)->first_arg, "exit") == 0)
		return (1);
	return (0);
}

int	select_built(t_cmd_line **node, t_myvars **my_vars)
{	
	char	*trim;

	if (strcmp((*node)->first_arg, "echo") == 0)
	{
		trim = ft_strtrim((*node)->arguments, " ");
		built_echo(trim);
		free(trim);
	}
	else if (strcmp((*node)->first_arg, "cd") == 0)
		built_cd(my_vars, (*node)->arguments);
	else if (strcmp((*node)->first_arg, "env") == 0)
		built_env(&(*my_vars)->my_env);
	else if (strcmp((*node)->first_arg, "export") == 0)
		built_export(&(*my_vars)->my_env,
			&(*my_vars)->export_env, (*node)->arguments);
	else if (strcmp((*node)->first_arg, "pwd") == 0)
		built_get_pwd();
	else if (strcmp((*node)->first_arg, "unset") == 0)
		built_unset(&(*my_vars)->my_env, \
		&(*my_vars)->export_env, (*node)->arguments);
	else if (strcmp((*node)->first_arg, "exit") == 0)
		built_exit((*node)->arguments, my_vars);
	if (bolean_built(node))
		return (1);
	return (0);
}
