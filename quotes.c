/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:31:53 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/20 18:55:20 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_dollar(char str, int *pair_quote, int *single_quote)
{
	if (str == '"' && *pair_quote == 0 && *single_quote == 0)
		(*pair_quote)++;
	else if (str == '"' && *pair_quote == 1)
		(*pair_quote)--;
	if (str == '\''  && *single_quote == 0 && *pair_quote == 0)
		(*single_quote)++;
	else if (str == '\''  && *single_quote == 1)
		(*single_quote)--;
	if (str == '$' && *single_quote == 0)
		return(1);
	return (0);
}

int	move_along_iterator(char *str)
{
	int count;

	count = 0;;
	while(str[count] )
	{
		if (check_is_spaces(str[count]) && count != 0)
			break;
		count++;
	}
	return (count);
}

char *routes_of_env(t_enviroment **myenv, char str)
{
	t_enviroment    *aux;
	char 			*content_env;

	content_env =  NULL;
	while (aux)
	{
		if (ft_strncmp(aux->env_var, str, move_along_iterator(str)) == 0)
		{
			content_env = ft_strldup(str, ft_point_strchr(str, '='));	
			break;
		}
		aux = aux->next;
	}
	return(content_env);
}

int	len_expand_str(t_enviroment **myenv, char *str)
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
		if (check_dollar(str[count], &flag[P_QUOTE], &flag[S_QUOTE]))
		{
			expand = routes_of_env(myenv, &str[count + 1]);
			count += move_along_iterator(&str[count]) - 1;
			len +=  ft_strlen(expand);
			free(expand);
		}
		len++;
		count++;
	}
	return(len);
}

char	 *expand_str(t_enviroment *myenv, char *str)
{
	char	*expand;
	char	*str_expand;
	int		len;
	int 	count;
	int		flag[2];
	
	flag[P_QUOTE] = 0;
	flag[S_QUOTE] = 0;
	len  = len_expand_str(myenv, str);
	str_expand = (char *)malloc(sizeof(char) * len + 1);
	while (str[count])
	{
		if(check_dollar(str[count], &flag[P_QUOTE], &flag[S_QUOTE]))
		{
			expand = routes_of_env(myenv, &str[count + 1]);
		}
	}
	
	
}