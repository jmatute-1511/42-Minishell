/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:23:12 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/24 18:52:06 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <sys/types.h>
#include <limits.h>

#define P_QUOTE 0 // Pair quotes

#define S_QUOTE 1 // single quotes

#define DOLLAR_SPACES "$ '\'' \"\n\t\v\f\r"

typedef struct	s_enviroment
{
char	*env_var;
void	*next;    
}				t_enviroment;

typedef struct	s_myvars
{
	char			*first_pwd;
	t_enviroment	*my_env;
	t_enviroment	*export_env;
}				t_myvars;

typedef struct	s_vars_env
{
	t_enviroment	*my_env;
	t_enviroment	*export_env;
}				t_vars_env;

typedef struct s_cmd_line
{
	char	*type;
	char	*first_arg;
	char	*arguments;
	char	*raw_cmd;
	void	*next;
}				t_cmd_line;

void			start_vars(t_myvars *myvars, char **envp) ;
char * 			ft_strchrdup_quote(char *str,char chr);
void			check_quotes(char str, int *pair_quote, int *single_quote);
int				first_filter_errors(char *str);
void			built_get_pwd(void);
void			built_env(t_enviroment **myenv);
void			built_echo(char *str);
void			open_directory(char *str);
void			built_cd(t_myvars *myvars,char *str);
t_enviroment	*ft_nodenew(char *new_var);
void			ft_nodeadd_back(t_enviroment **lst, t_enviroment **new);
void			ft_nodeadd_alphabet(t_enviroment **lst, t_enviroment **new);
void			free_lst(t_enviroment *node);
t_cmd_line		*ft_cmd_nodenew(char *raw_cmd, size_t len);
void			ft_cmds_nodeadd_back(t_cmd_line **lst, t_cmd_line **new);
int				ft_point_strchr(char *s, char c);
void			built_export(t_enviroment **my_env ,t_enviroment **export_env, char *str);
void			print_env(t_enviroment *export_env, char *option);
void			buil_unset(t_enviroment **myenv, t_enviroment **export_env, char *str);
char			*filtered_cmd(t_enviroment **myenv, char *str);
int				len_string(char *str);
t_cmd_line		*list_cmds(char *str);
void			print_cmd(t_cmd_line **lst);
int				ft_point_strstr(char *str);
char			*expand_str(t_enviroment *myenv, char *str);
char			*set_quotes(char *str);
void			init_nodes(t_cmd_line **lst_cmds, t_enviroment **myenv, char *str);
void			add_first_arg(t_cmd_line **node);
#endif