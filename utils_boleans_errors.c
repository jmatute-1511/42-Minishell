/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_boleans_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 19:03:29 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/25 16:28:52 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	bolean_errors_quotes(char *str)
{
	int	pair_quote;
	int	single_quote;
	int	count;

	count = 0;
	pair_quote = 0;
	single_quote = 0;
	while (str[count])
	{
		if (str[count] == '"' && pair_quote == 0 && single_quote == 0)
			pair_quote++;
		else if (str[count] == '"' && pair_quote == 1)
			pair_quote--;
		if (str[count] == '\'' && single_quote == 0 && pair_quote == 0)
			single_quote++;
		else if (str[count] == '\'' && single_quote == 1)
			(single_quote)--;
		count++;
	}
	if (pair_quote != 0 || single_quote != 0)
		return (1);
	return (0);
}

int	first_filter_errors(char *str)
{
	if (bolean_errors_quotes(str))
	{
		printf("Myshell: quotes : error\n");
		return (1);
	}
	return (0);
}

static int	null_str( char *str)
{
	if (str[0] == '\0')
	{
		printf("Myshell: %s : comand not found\n", str);
		return (1);
	}
	return (0);
}

int	cmd_not_found(t_cmd_line **node, t_enviroment **myenv)
{
	char	*str;
	char	**split_env;
	char	*cmd;

	if ((*node)->first_arg)
	{
		if (access((*node)->first_arg, X_OK) == 0)
			return (0);
		cmd = NULL;
		str = set_quotes((*node)->first_arg);
		if (null_str(str))
			return (1);
		free((*node)->first_arg);
		(*node)->first_arg = str;
		split_env = routes_of_path(myenv);
		if (split_env != NULL)
			cmd = access_cmd(split_env, str);
		if (cmd == NULL && bolean_built(node) == 0)
		{
			printf("Myshell: %s : comand not found\n", str);
			return (1);
		}
		free_matrix(split_env);
	}
	return (0);
}
