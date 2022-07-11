/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boleans_first_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:57:03 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/10 21:16:29 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int bolean_errors_quotes(char *str)
{
	int pair_quote;
	int single_quote;
	int count;
	
	count = 0;
	pair_quote = 0;
	single_quote = 0;
	while(str[count])
	{
		if (str[count] == '"' && pair_quote == 0 && single_quote == 0)
			pair_quote++;
		else if (str[count] == '"' && pair_quote == 1)
			pair_quote--;
		if (str[count] == '\''  && single_quote == 0 && pair_quote == 0)
			single_quote++;
		else if (str[count] == '\''  && single_quote == 1)
			(single_quote)--;
		count++;
	}
	if(pair_quote != 0 || single_quote != 0)
		return(1);
	return (0);
	
}

int first_filter_errors(char *str)
{
	if (bolean_errors_quotes(str))
	{
		printf("Myshell: quotes : error\n");
		return(1);
	}
	return (0);
}

int cmd_not_found(t_cmd_line **node, t_enviroment **myenv)
{
	char 	*str;
	char 	**split_env;
	char	*cmd;
	
	if ((*node)->first_arg)
	{
		cmd = NULL;
		str = set_quotes((*node)->first_arg);
		free((*node)->first_arg);
		(*node)->first_arg = str;
		split_env = routes_of_path(myenv);
		if(split_env != NULL) 
			cmd = access_cmd(split_env, str);
		if(cmd == NULL && bolean_built(node) == 0)
		{
			printf("Myshell: %s : comand not found\n", str);
			return (1);
		}
	}
	return (0);
}

int hdoc_without_arg(char *hdoc, char type)
{
	int		count;
	int		signal;
	int		flag[2];
	
	count = 0;
	signal = 0;
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;
	if(!hdoc)
		return (0);
	while (hdoc[count])
	{
		if(hdoc[count] == type && hdoc[count + 1] != type && flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0)
		{
			count++;
			while (hdoc[count])
			{
				if((hdoc[count] == '<' || hdoc[count] == '>') && signal == 0)
					return (1);
				else if (hdoc[count] != ' ' || hdoc[count] != '<' || hdoc[count] != '>')
					signal = 1;
				count++;
			}
			if (signal == 0)
				return (1);
		}
		check_quotes(hdoc[count], &flag[P_QUOTE], &flag[S_QUOTE]);
		count++;
	}
	return (0);
}

int error_cmd(t_cmd_line **node, t_myvars **my_vars)
{
	(void)my_vars;
	if ((*node)->arguments == NULL)
		return(0);
	if ((*node)->raw_cmd == NULL)
	{
		printf("Myshell: parse error near '|' \n");
		return (1);
	}
	if (hdoc_without_arg((*node)->raw_cmd, '<'))
	{
		printf("Myshell: parse error near \n");
		return (1);
	}
	if (hdoc_without_arg((*node)->raw_cmd, '>'))
	{
		printf("Myshell: parse error near \n");
		return (1);
	}
	return (0);
}

