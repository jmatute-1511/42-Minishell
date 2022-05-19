/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 20:28:30 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/19 17:13:22 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_nodeadd_front(t_enviroment **alst, t_enviroment *new) // add in front new node of enviroment variables to lst
{
	if (alst && new)
	{
		new->next = (*alst);
		(*alst) = new;
	}
}


t_enviroment	*ft_nodenew(char *new_var) // create a new node of enviroment variables
{
	t_enviroment	*new;

	new = malloc(sizeof(t_enviroment));
	if (!new)
		return (NULL);
	new->env_var = ft_strdup(new_var);
	new->next = NULL;
	return (new);
}


void	ft_nodeadd_back(t_enviroment **lst, t_enviroment **new) // add a new node of enviroment variables to the end of the list
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

void	ft_nodeadd_alphabet(t_enviroment  **lst, t_enviroment **new) // alphabetize the list of enviroment variables 
{
	t_enviroment	*aux;
	t_enviroment	*aux_node;
	int				a;
	
	if ((*lst) == NULL)
		(*lst)= (*new);
	else if(ft_strcmp((*lst)->env_var,(*new)->env_var) > 0) 
	{																	// to make short
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
