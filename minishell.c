/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:46:48 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/11 22:01:34 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc,char **argv,char **envp)
{
	t_myvars myvars;
	char    *str;

	start_vars(&myvars,envp);
	if (!myvars.my_env)
		return(0);
	//print_env(myvars.my_env);
	printf("===============================================================================\n=============================================================\n");
	print_env(myvars.alphabet_env);
	/*while (1)
	{
		str = readline("🧠🧠🧠Myshell🧠🧠🧠 --->");
		if (ft_strncmp(str,"echo", ft_strlen("echo")) == 0)
			built_echo(str);
		else if ((ft_strncmp(str,"export", ft_strlen("export")) == 0))
				built_export(&myvars.my_env, &myvars.alphabet_env, &str[ft_strlen("export") + 1]);
		if (ft_strcmp(str,"exit") == 0)
			break;
	}*/
}