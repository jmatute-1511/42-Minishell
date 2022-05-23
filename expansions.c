/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:31:53 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/23 13:59:30 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_dollar(char str, int *pair_quote, int *single_quote)
{
	if (str == '"' && *pair_quote == 0 && *single_quote == 0)
		(*pair_quote) += 1;
	else if (str == '"' && *pair_quote == 1)
		(*pair_quote) -= 1;
	if (str == '\''  && *single_quote == 0 && *pair_quote == 0)
		(*single_quote) += 1;
	else if (str == '\''  && *single_quote == 1)
		(*single_quote) -= 1;
	if (str == '$' && *single_quote == 0)
		return(1);
	return (0);
}

char *routes_of_env(t_enviroment *myenv, char *str)
{
	t_enviroment    *aux;
	char			*aux_expand;
	char			*expand;
	char 			*content_env;

	content_env =  NULL;
	aux =  myenv;
	aux_expand  = ft_strldup(str, ft_point_strstr(str));
	expand = ft_strjoin(aux_expand, "=");
	while (aux)
	{
		if (ft_strncmp(aux->env_var, expand,ft_strlen(expand)) == 0)
		{
			content_env = ft_strdup(&aux->env_var[ft_strlen(expand) + 1]);
			break;
		}
		aux = aux->next;
	}
	free(expand);
	free(aux_expand);
	return(content_env);
}

int	len_expand_str(t_enviroment *myenv, char *str)
{
	int		count;
	int		len;
	int		flag[2];
	char 	*expand;

	count = 0;
	len  = 0;
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;
	while (str[count])
	{
		while (check_dollar(str[count], &flag[P_QUOTE], &flag[S_QUOTE]))
		{
			count++;
			expand = routes_of_env(myenv, &str[count]);
			count += ft_point_strstr(&str[count]);
			if (expand != NULL)
			{
				len +=  ft_strlen(expand);
				free(expand);
			}
		}
		len++;
		count++;
	}
	return(len);
}

void	cpy_expand(t_enviroment *myenv, char *str, char **str_expand,\
 int *count2)
{
	char	*expand;
	char 	*aux;
	int		count;

	aux = *str_expand;
	expand = routes_of_env(myenv, str);
	count = 0;
	if	(expand != NULL)
	{
		while (expand[count])
		{
			aux[*count2] = expand[count];
			count++;
			*count2 += 1;
		}
	}
	free(expand);
}

char	 *expand_str(t_enviroment *myenv, char *str)
{
	char	*str_expand;
	int 	count;
	int		count2;
	int		flag[2];
	
	count = 0;
	count2 = 0;
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;
	str_expand = malloc(sizeof(char) * (len_expand_str(myenv, str)+ 1));
	while (str[count])
	{
		while (check_dollar(str[count], &flag[P_QUOTE], &flag[S_QUOTE]))
		{
			count++;
			cpy_expand(myenv, &str[count], &str_expand, &count2);
			count += ft_point_strstr(&str[count]);
		}
		str_expand[count2] = str[count];
		count2++;
		count++;
	}
	str_expand[count2] = '\0';
	return(str_expand);
}