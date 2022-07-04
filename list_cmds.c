/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:52:40 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/04 18:04:22 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int check_pipe(char str, int *pair_quote, int *single_quote)
{
	if (str == '"' && *pair_quote == 0 && *single_quote == 0)
		(*pair_quote)++;
	else if (str == '"' && *pair_quote == 1)
		(*pair_quote)--;
	if (str == '\''  && *single_quote == 0 && *pair_quote == 0)
		(*single_quote)++;
	else if (str == '\''  && *single_quote == 1)
		(*single_quote)--;
	if (str == '|' && *pair_quote == 0 && *single_quote == 0)
		return(1);
	return (0);
}

int len_raw_cmd(char *str)
{
	int count;
    int pair_quote;
    int  single_quote;
	
	count  = 0;
	single_quote = 0;
	pair_quote = 0;
	while (str[count])
	{
		if (str[count] == '"'  && pair_quote == 0 && single_quote == 0)
			pair_quote++;
		else if (str[count] == '"'  && pair_quote == 1)
			pair_quote--;
		if (str[count] == '\''  && single_quote == 0 && pair_quote == 0)
			single_quote++;
		else if (str[count] == '\''  && single_quote == 1)
			single_quote--;
        if (str[count] == '|' && pair_quote == 0 && single_quote == 0 && count != 0)
            break;
		count++;
	}
	return (count);
}


t_cmd_line      *list_cmds(char *str)
{
    int			count;
	int			pipe;	
	t_cmd_line	*lst;
	t_cmd_line	*add_back;
    
	count  = 0;
	lst = NULL;
	while (str[count])
	{
		pipe = len_raw_cmd(&str[count]);
		add_back = ft_cmd_nodenew(&str[count], pipe);
		ft_cmds_nodeadd_back(&lst, &add_back);
		count += pipe;
	}
	return	(lst);
}

void print_cmd(t_cmd_line **lst)
{
	t_cmd_line *aux;

	aux = (*lst);
	while (aux)
	{
		printf("INPUT :%s\n",aux->input);
		printf("OUTPUT :%s\n", aux->output);
		printf("FIRST ARG :%s\n",aux->first_arg);
		printf("ARGUMENTS :%s\n", aux->arguments);
		printf("RAW CMD :%s\n", aux->raw_cmd);
		printf("------------------------------------------------------\n");
		aux = aux->next;
	}
}