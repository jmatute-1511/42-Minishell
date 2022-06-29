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

void signal_handler(int signum)
{
	int g_proc;

	g_proc = 0;
	if (signum == SIGINT && g_proc != 0)
	{
		kill(0, SIGCONT);
    	write(0, "\n", 1);
	}
	if (signum == SIGINT && g_proc == 0)
	{
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int main(int argc,char **argv,char **envp)
{
	t_myvars	*myvars;
	t_cmd_line	*lst;
	char    	*str;
	int			*bolean;
	
	signal(SIGINT,signal_handler);
	signal(SIGQUIT, SIG_IGN);
	myvars = start_vars(myvars,envp);
	if (!myvars->my_env)
		return(0);
	while (1)
	{
		str = readline(ROJO_T"Myshell%>"VERDE_T);
		if (str == NULL)
		{
			printf("exit\n");
			return (0);
		}
		add_history(str);
		if(init_nodes(&lst, &myvars->my_env, str) == 0)
		{
			if (lst)
				execute_cmds(&lst,&myvars);
		}
		//print_cmd(&lst);
	}
}