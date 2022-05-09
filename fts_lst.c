/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 20:28:30 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/08 16:13:24 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_enviroment	*ft_nodenew(char *new_var)
{
	t_enviroment	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->env_var = new_var;
	new->next = NULL;
	return (new);
}

void free_lst(t_enviroment *node)
{
    t_enviroment *aux;

    aux = node;
    free(node->env_var);
    free(node);
}

void	ft_nodeadd_back(t_enviroment **lst, t_enviroment *new)
{
	t_enviroment	*aux;
	
	if (lst)
	{
		if (*lst == NULL)
		{
			(*lst) = new;
			return ;
		}
		aux = (*lst);
		while (aux->next)
			aux = aux->next;
		aux->next = new;
	}
}

void	ft_nodeadd_alphabet(t_enviroment **lst, t_enviroment *new)
{
	t_enviroment	*aux;
	t_enviroment	*aux_node;
	
	if (lst)
	{
		if (*lst == NULL)
		{
			(*lst) = new;
			return ;
		}
		aux = (*lst);
		if(ft_strcmp(aux->env_var, new->env_var) > 0 && aux->next == NULL)
		{
			new->next = aux;
			(*lst) = new;
		}
		while (aux->next)
		{
			if (ft_strcmp(aux->env_var, new->env_var) > 0)
				break;
			aux_node = aux;
			aux = aux->next;
		}
		if (ft_strcmp(aux->env_var, new->env_var) > 0)
		{
			aux_node->next = new;
			new->next = aux;
		}
		else 
			ft_nodeadd_back(lst,new);
	}
}

