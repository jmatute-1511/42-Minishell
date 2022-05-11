/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 20:28:30 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/11 22:08:41 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_nodeadd_front(t_enviroment **alst, t_enviroment *new)
{
	if (alst && new)
	{
		new->next = (*alst);
		(*alst) = new;
	}
}
int	ft_nodesize(t_enviroment *lst)
{
	size_t	len;
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

void	ft_nodeadd_alphabet(t_enviroment  	**lst, t_enviroment *new)
{
	t_enviroment	*aux;
	
	if (lst == NULL)
		*lst = new;
	else if (ft_nodesize(*lst) == 1)
	{
		if (ft_strcmp((*lst)->env_var, new->env_var) > 0)
			ft_nodeadd_front(lst, new);
		else
			ft_nodeadd_back(lst, new);
	}
	else
	{
		aux = (*lst);
		while (aux)
		{
			if (ft_strcmp((*lst)->env_var, new->env_var) > 0)
			{
				ft_nodeadd_front(&aux, new);
				break;
			}
			else if (aux->next == NULL)
				ft_nodeadd_back(&aux, new);
			aux =aux->next;
		}
	}
}

