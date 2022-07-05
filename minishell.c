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

int g_proc; // id del fork.

void signal_handler(int signum)
{
	printf("ID: %i, SIGNUM: %i\n", g_proc, signum);
	if (signum == SIGINT && g_proc != 0)
	{
		kill(g_proc, SIGCONT);
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
	
	signal(SIGINT,signal_handler);
	signal(SIGQUIT, SIG_IGN);
	myvars = start_vars(myvars,envp);
	if (!myvars->my_env)
		return(0);
	//print();
	while (1)
	{
		str = NULL;
		str = readline(ROJO_T"Myshell%---->"COLOR_RESET);
		if (str == NULL)
		{
			printf("exit\n");
			return (0);
		}
		if (ft_strcmp(str,"") != 0)
			add_history(str);
		init_nodes(&lst, &myvars->my_env, str);
		if(lst)
			execute_cmds(&lst, myvars);
		//print_cmd(&lst);
		free(str);
	}
}