/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:13:44 by jmatute-          #+#    #+#             */
/*   Updated: 2022/06/21 20:47:33 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_back_pipe(t_pipes **lst, t_pipes **pipes)
{
    t_pipes *aux;

    
    if((*lst))
    {
        aux = (*lst);
        while (aux->next != NULL)
            aux = aux->next;
        aux->next = (*pipes);
        (*pipes)->next = NULL;
        (*pipes)->prev = aux;
    }
}

t_pipes *create_pipes(int npipes)
{
    int a;
    t_pipes *pipes;
    t_pipes *aux;
    
    a = 0;
    pipes = malloc(sizeof(t_pipes));
    pipes->next = NULL;
    pipes->prev = NULL;
    while (a < npipes - 1)
    {
        aux = malloc(sizeof(t_pipes));
        add_back_pipe(&pipes, &aux);
        a++;
    }
    return(pipes);
}

int size_of_lst(t_cmd_line **lst)
{
    int a;
    t_cmd_line *aux;

    a = 0;
    aux = (*lst);
    while(aux->next)
    {
        aux = aux->next;
        a++;
    }
    return(a);
}

char *find_path_exec(char *str, t_enviroment ** my_env)
{
    char    **split;
    char    *path;

    split = routes_of_path(my_env);
    path = access_cmd(split, str);
    return (path); 
}

void son_shell_first(t_cmd_line **cmd,t_pipes **pipes, char **envp_m,  t_myvars **my_vars)
{
    char *path;

    path = find_path_exec((*cmd)->first_arg, &(*my_vars)->my_env);
   // | dprintf(2, " SON FIRST %s\n",path);
    dup2((*pipes)->fd[WRITE_P], STDOUT_FILENO);
    close((*pipes)->fd[READ_P]);
    close((*pipes)->fd[WRITE_P]);
    if (select_built(cmd, (*my_vars)) == 0)
        execve(path,ft_split((*cmd)->arguments, ' '), envp_m);
}

void son_shell_med(t_cmd_line **cmd,t_pipes **pipes, char **envp_m, t_myvars **my_vars)
{
    char *path;

    path = find_path_exec((*cmd)->first_arg, &(*my_vars)->my_env);
   // dprintf(2, "SON MED %s\n",path);
    dup2((*pipes)->prev->fd[READ_P], STDIN_FILENO);
    dup2((*pipes)->fd[WRITE_P], STDOUT_FILENO);
    close((*pipes)->fd[READ_P]);
    close((*pipes)->fd[WRITE_P]);
    if (select_built(cmd, (*my_vars)) == 0)
        execve(path, ft_split((*cmd)->arguments, ' '), envp_m);
    
}
void son_shell_last(t_cmd_line **cmd,t_pipes **pipes, char **envp_m, t_myvars **my_vars)
{
    char *path;

    path = find_path_exec((*cmd)->first_arg, &(*my_vars)->my_env);
  //  dprintf(2, " SON LAST%s\n",path);
    dup2((*pipes)->prev->fd[READ_P], STDIN_FILENO);
    close((*pipes)->fd[READ_P]);
    close((*pipes)->fd[WRITE_P]);
    if (select_built(cmd, (*my_vars)) == 0)
        execve(path, ft_split((*cmd)->arguments, ' '), envp_m);
}
void select_child(t_cmd_line **cmd,t_pipes **pipes, char **envp_m, t_myvars **my_vars)
{
    if ((*pipes)->prev == NULL)
        son_shell_first(cmd,pipes, envp_m, my_vars);
    else if ((*pipes)->prev != NULL && (*pipes)->next != NULL)
        son_shell_med(cmd,pipes, envp_m, my_vars);
    else if ((*pipes)->next == NULL)
        son_shell_last(cmd,pipes, envp_m, my_vars);
}

int execute_cmds(t_cmd_line **cmds, t_myvars **my_vars)
{
    int     n_childs;
    int     status;
    int     pid;
    int     aux;
    int     wait;
    int     *array;
    t_cmd_line *node;
    t_pipes *pipes;
    
    n_childs = size_of_lst(cmds);
    pipes = create_pipes(n_childs);
    array = malloc(sizeof(int) * n_childs);
    aux = 0;
    wait = 0; 
    node =  (*cmds);
    while (aux <= n_childs)
    {
        pid = fork();
        if (pid == 0)
        {   
            select_child(&node, &pipes, (*my_vars)->m_envp, my_vars);
            array[aux] = pid;
        }
        node = node->next;
        aux++;
    }
    while (wait < n_childs)
    {
        waitpid(array[wait],&status, 0);
        wait++;
    }
    return (0);
}