/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:23:12 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/25 17:16:25 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <string.h>
# include <curses.h>
# include <term.h>
# include <fcntl.h>

# define BYEL "\e[1;33m"
# define YEL "\e[0;33m"
# define GRN "\e[0;32m"
# define BGRN "\e[1;32m"	
# define BLU "\e[0;34m"
# define BBLU "\e[1;34m"
# define COLOR_RESET "\e[0m"
# define P_QUOTE 0 // Pair quotes
# define S_QUOTE 1 // single quotes
# define FIRST 0
# define FINAL 1
# define READ_P 0
# define WRITE_P 1

typedef struct s_enviroment
{
	char	*env_var;
	void	*next;
}				t_enviroment;
typedef struct s_pipes
{
	int				fd[2];
}				t_pipes;
typedef struct s_vars_env
{
	t_enviroment	*my_env;
	t_enviroment	*export_env;
}				t_vars_env;

typedef struct s_cmd_line
{
	char	*input;
	char	*output;
	char	*first_arg;
	char	*arguments;
	char	*raw_cmd;
	void	*next;
}				t_cmd_line;

typedef struct s_myvars
{
	int				stat;
	char			*hdoc;
	int				n_childs;
	char			**m_envp;
	char			*first_pwd;
	t_enviroment	*pwd;
	t_enviroment	*home;
	t_enviroment	*my_env;
	t_enviroment	*old_pwd;
	t_enviroment	*ultimate_cmd;
	t_enviroment	*export_env;
	t_pipes			*pipe_hdoc;
}				t_myvars;

int	g_proc;

void			kill(int thread, int signal);
void			rl_replace_line(const char *text, int clear_undo);
t_myvars		*start_vars(char **envp);
char			*ft_strchrdup_quote(char *str, char *chr);
void			check_quotes(char str, int *pair_quote, int *single_quote);
int				first_filter_errors(char *str);
void			built_get_pwd(void);
void			built_env(t_enviroment **myenv);
void			built_echo(char *str);
void			open_directory(char *str);
void			built_cd(t_myvars **myvars, char *str);
void			built_exit(char *str, t_myvars **my_vars);
t_enviroment	*ft_nodenew(char *new_var);
void			ft_nodeadd_back(t_enviroment **lst, t_enviroment **new);
void			ft_nodeadd_alphabet(t_enviroment **lst, t_enviroment **new);
void			free_lst(t_enviroment *node);
t_cmd_line		*ft_cmd_nodenew(char *raw_cmd, size_t len);
void			ft_cmds_nodeadd_back(t_cmd_line **lst, t_cmd_line **new);
int				ft_point_strchr(char *s, char c);
void			built_export(t_enviroment **my_env,
					t_enviroment **export_env, char *str);
void			print_env(t_enviroment *export_env, char *option);
void			built_unset(t_enviroment **myenv,
					t_enviroment **export_env, char *str);
char			*filtered_cmd(t_enviroment **myenv, char *str);
int				len_string(char *str);
t_cmd_line		*list_cmds(char *str);
void			print_cmd(t_cmd_line **lst);
int				ft_point_strstr(char *str);
char			*expand_str(t_myvars *my_vars, char *str);
char			*set_quotes(char *str);
int				init_nodes(t_cmd_line **lst_cmds,
					t_myvars **mmyvars, char *str);
void			add_first_arg(t_cmd_line **node, t_enviroment **myenv);
char			**routes_of_path(t_enviroment **myenv);
char			*access_cmd(char **split_of_path, char *str);
int				error_cmd(t_cmd_line **node);
void			free_lst_cmds(t_cmd_line **lst);
int				select_built(t_cmd_line **node, t_myvars **my_vars);
int				bolean_built(t_cmd_line **node);
int				execute_cmds(t_cmd_line **nodes, t_myvars **my_vars);
int				size_of_lst(t_cmd_line **lst);
void			heredoc_initializer(char *text, t_myvars **my_vars, int flag);
void			signal_handler(int signum);
void			redirect_input(char *file);
void			redirect_output(char *file);
void			redirect_output_double(char *file);	
int				cmd_not_found(t_cmd_line **node, t_enviroment **myenv);
t_enviroment	*find_path(t_enviroment *my_env, char *str);
void			handle_output(t_cmd_line *node);
void			handle_input(t_cmd_line *node, t_myvars **my_vars);
int				bolean_built(t_cmd_line **node);
int				cmd_not_found(t_cmd_line **node, t_enviroment **myenv);
t_enviroment	*find_path(t_enviroment *my_env, char *str);
int				add_hdocs(t_cmd_line **node, char *str);
void			expand_continue(t_cmd_line **node);
void			capture_arguments(t_cmd_line **node, char *str);
void			capture_first_arg(t_cmd_line **node);
char			**enviroment_matrix(t_enviroment *my_env);
void			heredoc_finish(t_myvars **my_vars);
void			handle_heredoc(t_cmd_line *node, t_myvars **my_vars);
void			free_cmds(t_cmd_line **lst);
void			shell_level(char **m_envp);
void			free_vars(t_myvars **my_vars);
#endif