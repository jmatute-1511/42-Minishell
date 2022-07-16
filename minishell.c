/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:46:48 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/16 18:31:54 by jmatute-         ###   ########.fr       */
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

void free_cmds(t_cmd_line **lst)
{
	t_cmd_line *aux;
	t_cmd_line *aux2;
	
	aux2 = NULL;
	aux = (*lst);
	while (aux)
	{
		if (aux->input)
			free(aux->input);
		if(aux->output)
			free(aux->output);
		if (aux->first_arg)
			free(aux->first_arg);
		if(aux->arguments)
			free(aux->arguments);
		if(aux->raw_cmd)
			free(aux->raw_cmd);
		aux2 = aux;
		aux = aux->next;
		free(aux2);
	}
	(*lst) = NULL;	
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
		g_proc = 0;
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
