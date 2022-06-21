/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:46:48 by jmatute-          #+#    #+#             */
/*   Updated: 2022/06/21 20:06:16 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc,char **argv,char **envp)
{
	t_myvars	*myvars;
	t_cmd_line	*lst;
	char    	*str;
	int			*bolean;
	

	myvars = start_vars(myvars,envp);
	if (!myvars->my_env)
		return(0);
	while (1)
	{
		str = readline(ROJO_T"Myshell%>"VERDE_T);
		add_history(str);
		if(init_nodes(&lst, &myvars->my_env, str) == 0)
		{
			if (lst)
				execute_cmds(&lst,&myvars);
		}
		//print_cmd(&lst);
	}
}