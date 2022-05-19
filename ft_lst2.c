/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:00:35 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/19 17:10:02 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_nodesize(t_enviroment *lst) // calculate lenght of list
{
	size_t			len;
	t_enviroment	*aux;

	len = 0;
	aux = lst;
	while (aux)
	{
		aux = aux->next;
		len++;
	}
	return (len);
}

void free_lst_node(t_enviroment *node) // free enviroment vars
{
    t_enviroment *aux;

    aux = node;
    free(node->env_var);
    free(node);
}

t_cmd_line	*ft_cmd_nodenew(char *raw_cmd) // create new node of cmds 
{
	t_cmd_line	*new;

	new = malloc(sizeof(t_cmd_line));
	if (!new)
		return (NULL);
	new->raw_cmd = ft_strdup(raw_cmd);
	new->next = NULL;
	return (new);
}

void	ft_cmds_nodeadd_back(t_cmd_line **lst, t_cmd_line **new) // add a new node of cmds to the end of list
{
	t_cmd_line	*aux;
	
	if (lst)
	{
		if (*lst == NULL) 
		{
			(*lst) = *new;
			return ;
		}
		aux = (*lst);
		while (aux->next)
			aux = aux->next;
		aux->next = *new;
	}
}