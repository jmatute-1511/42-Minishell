/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acces_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:56:32 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/09 03:07:10 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **routes_of_path(t_enviroment **myenv)
{
	t_enviroment    *aux;
	char            **split_of_path;
	int count;

	count = 0;
	split_of_path =  NULL;
	aux = (*myenv);
	while (aux)
	{
		if (ft_strncmp(aux->env_var, "PATH=", 5) == 0)
		{
			split_of_path = ft_split(&aux->env_var[5], ':');
			break;
		}
		aux = aux->next;
	}
	return(split_of_path);
}

char *access_cmd(char **split_of_path, char *str)
{
	int count;
	char	*cmd;

	count  = 0;
	if(access(str, X_OK) == 0)
		return(str);
	else if(ft_strncmp("./", str, 2) == 0)
	{
		if (access(str, X_OK))
			return(str);
	}
	if (split_of_path)
	{
		while(split_of_path[count])
		{
			cmd = ft_strnjoin(3, split_of_path[count], "/", str);
			if(access(cmd, X_OK) == 0)
				return(cmd);
			free(cmd);
			cmd = NULL;
			count++;
		}
	}
	return(NULL);
}