/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:46:48 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/19 16:43:49 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc,char **argv,char **envp)
{
	t_myvars myvars;
	char    *str;
	int count;
	t_cmd_line *lst;
	

	start_vars(&myvars,envp);
	if (!myvars.my_env)
		return(0);
	count = 0;
	while (1)
	{
		str = readline("🧠🧠🧠Myshell🧠🧠🧠 --->");
		lst = list_cmds(str);
		print_cmd(&lst);
		// if (ft_strnstr(str, "echo", ft_strlen(str)) != NULL)
		// 	built_echo(str);
		// else if (ft_strnstr(str, "export", ft_strlen(str)) != NULL)
		// 	built_export(&myvars.my_env, &myvars.export_env,ft_strnstr(str, "export", ft_strlen(str)));
		// else if(ft_strnstr(str, "unset", ft_strlen(str)) != NULL)
		// 	buil_unset(&myvars.my_env, &myvars.export_env, ft_strnstr(str, "unset", ft_strlen(str)));
		// else if(ft_strnstr(str, "env", ft_strlen(str)) != NULL)
		// 	built_env(&myvars.my_env); 
		// if (ft_strnstr(str, "exit", ft_strlen(str)) != NULL)
		// 	break;
		// print_env(myvars.my_env, "env");
		// printf("\n\n\n");
		// print_env(myvars.export_env, "export");
		
	}
}