/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:46:48 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/04 21:08:31 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print()
{
	char *str;
	int a;
	
	a = open("./title.txt",O_RDONLY);
	read(a, str, 638);
	printf(BBLU"%s\n", str);
}

int main(int argc,char **argv,char **envp)
{
	t_myvars	*myvars;
	t_cmd_line	*lst;
	char    	*str;
	int			*bolean;
	

	myvars = start_vars(myvars,envp);
	if (!myvars->my_env)
		return(0);
	print();
	while (1)
	{
		str = NULL;
		str = readline(ROJO_T"Myshell%---->"COLOR_RESET);
		if (ft_strcmp(str,"") != 0)
			add_history(str);
		init_nodes(&lst, &myvars->my_env, str);
		if(lst)
			execute_cmds(&lst, myvars);
		//print_cmd(&lst);
		free(str);
	}
}