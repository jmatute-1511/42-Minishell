/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:46:48 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/09 12:55:27 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum)
{
	printf("%i\n", g_proc);
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

int main(int argc,char **argv,char **envp)
{
	t_myvars	*myvars;
	t_cmd_line	*lst;
	char		*str;
	int			*bolean;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	myvars = start_vars(myvars,envp);
	/*if (!myvars->my_env)
		return(0);*/
	while (1)
	{
		str = NULL;
		str = readline(ROJO_T"Myshell%---->"COLOR_RESET);
		if (str == NULL)
			return (exit_signal());
		if (ft_strcmp(str, "") != 0)
			add_history(str);
		init_nodes(&lst, &myvars, str);
		//print_cmd(&lst);
		if(lst)
			execute_cmds(&lst, &myvars);
		free(str);
	}
}
