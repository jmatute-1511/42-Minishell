/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:53:55 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/05 22:43:17 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_path(char **envp, char *str)
{
	int	i;

	i = 0;
	while (envp[i] != 0)
	{
		if (ft_strncmp(envp[i], str, ft_strlen(str)) == 0)
			return (i);
		i++;
	}
	return (0);
}

static void change_location(char **pwd, char *str)
{
    char  *current;

    chdir(str);
    current = getcwd(NULL, 0);
   (*pwd) = ft_strjoin("PWD=",current);
 //   printf("%s\n", (*pwd));
}

void built_cd(t_myvars *myvars,char *str)
{
    int pwd;

    if (access(str, X_OK) != 0 || *myvars->enviroment == NULL)
        return ;    
    pwd = find_path(myvars->enviroment, "PWD=");
    if (ft_strncmp(myvars->enviroment[pwd],"PWD=", ft_strlen("PWD=")) == 0)
        change_location(&myvars->enviroment[pwd], str);
}