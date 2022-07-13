/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:46:48 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/11 18:37:39 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT && g_proc != 0)
	{
		kill(g_proc, SIGCONT);
		write(0, "\n", 1);
	}
	else if (signum == SIGINT && g_proc == 0)
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
	char		*str;

	myvars = NULL;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	(void)argc;
	(void)argv;
	myvars = start_vars(myvars,envp);
	while (1)
	{
		g_proc = 0;
		str = NULL;
		str = readline(ROJO_T"Myshell%---->"COLOR_RESET);
		if (str == NULL)
		{
			printf("exit\n");
			return (0);
		}
		if (ft_strcmp(str, "") != 0)
			add_history(str);
		if (init_nodes(&lst, &myvars, str) == 0)
		{
			if(lst)
				execute_cmds(&lst, &myvars);
		}
		free(str);
	}
}
