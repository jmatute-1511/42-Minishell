/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:46:48 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/15 23:41:20 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum)
{
	
	if (signum == SIGINT && g_proc > 0)
	{
		kill(g_proc, SIGCONT);
		// write(0, "\n", 1);
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
	}
	else if (signum == SIGINT && g_proc == 0)
	{
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGINT && g_proc < 0)
	{
		// write(0, "\n", 1);
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
	}
}
void print(void)
{
	printf(YEL"                                   __              ___    ___      \n");
	printf(YEL"           __          __         /\\ \\            /\\_ \\  /\\_ \\     \n");
	printf(BYEL"  ___ ___ /\\_\\    ___ /\\_\\    ____\\ \\ \\___      __\\//\\ \\ \\//\\ \\    \n");
	printf(BGRN"/' __` __`\\/\\ \\ /' _ `\\/\\ \\  /',__\\\\ \\  _ `\\  /'__`\\\\ \\ \\  \\ \\ \\   \n");
	printf(GRN"/\\ \\/\\ \\/\\ \\ \\ \\/\\ \\/\\ \\ \\ \\/\\__, `\\\\ \\ \\ \\ \\/\\  __/ \\_\\ \\_ \\_\\ \\_ \n");
	printf(BLU"\\ \\_\\ \\_\\ \\_\\ \\_\\ \\_\\ \\_\\ \\_\\/\\____/ \\ \\_\\ \\_\\ \\____\\/\\____\\/\\____\\\n");
	printf(BBLU" \\/_/\\/_/\\/_/\\/_/\\/_/\\/_/\\/_/\\/___/   \\/_/\\/_/\\/____/\\/____/\\/____/\n");
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
	print();
	myvars = start_vars(myvars,envp);
	while (1)
	{
		str = NULL;
		str = readline(YEL"Myshell%---->"COLOR_RESET);
		if (str == NULL)
		{
			printf("exit\n");
			return (0);
		}
		if (ft_strcmp(str, "") != 0)
			add_history(str);
		if (init_nodes(&lst, &myvars, str) == 0)
		{
			//print_cmd(&lst);
			if(lst)
				execute_cmds(&lst, &myvars);
		}
		free(str);
	}
}
