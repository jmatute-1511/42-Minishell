/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 20:28:30 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/14 03:18:52 by jmatute-         ###   ########.fr       */
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

t_enviroment	*ft_nodenew(char *new_var)
{
	t_enviroment	*new;

	new = malloc(sizeof(t_enviroment));
	if (!new)
		return (NULL);
	new->env_var = ft_strdup(new_var);
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

void	ft_nodeadd_back(t_enviroment **lst, t_enviroment **new)
{
	t_enviroment	*aux;
	
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

void	ft_nodeadd_alphabet(t_enviroment  **lst, t_enviroment **new)
{
	t_enviroment	*aux;
	t_enviroment	*aux_node;
	int				a;
	
	if ((*lst) == NULL)
		(*lst)= (*new);
	else if(ft_strcmp((*lst)->env_var,(*new)->env_var) > 0)
	{
		 (*new)->next = (*lst) ;
		 (*lst) = (*new);
	}
	else
	{
		aux = (*lst);
		aux_node = NULL;
		while(aux)
		{
			if (ft_strcmp(aux->env_var, (*new)->env_var) > 0 && aux_node)
			{
				aux_node->next = (*new);
				(*new)->next = aux;
				break;
			}
			aux_node = aux;
			aux = aux->next;
		}
		if (aux == NULL)
			aux_node->next = (*new);
		
	}
}

