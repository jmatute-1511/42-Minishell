/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_comand_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:36:26 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/18 18:56:21 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int check_quotes(char *str)
{
	int count;
	int simple_quote;
	int pair_quote;

	pair_quote = 0;
	simple_quote = 0;
	count = 0;
	while (str[count] )
	{
		if (str[count] == '"'  && pair_quote == 0 && simple_quote == 0)
			pair_quote++;
		else if (str[count] == '"'  && pair_quote == 1)
			pair_quote--;
		if (str[count] == '\''  && simple_quote == 0 && pair_quote == 0)
			simple_quote++;
		else if (str[count] == '\''  && simple_quote == 1)
			simple_quote--;
		count++;
	}
	if (pair_quote != 0  || simple_quote != 0)
		return (1);
	return (0);
}

int check_is_spaces(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f' || c == '\r'  \
	|| c == '$')
		return (1);
	return (0);
}

int	move_along_iterator(char *str)
{
	int count;

	count = 0;;
	while(str[count]  )
	{
		if (check_is_spaces(str[count]))
			break;
		count++;
	}
	return (count);
}

char *get_expand(char *str)
{
	int 	count;
	int 	flag;
	char	*aux;

	count = 0;
	flag = check_is_spaces(str[count]);
	while (str[count] && flag != 1)
	{	
		count++;
		flag = check_is_spaces(str[count]);
	}
	if (count > 0)
	{
		aux = malloc(sizeof(char) * count + 2);
		count = 0;
		while (aux[count] < count)
		{
			aux[count] = str[count]; 
			count++;
		}
		aux[count] = '=';
		aux[count + 1] = '\0';
		return(aux);
	}
	return(NULL);
}

char  *find_path_expand(t_enviroment **my_env, char *str)
{
	t_enviroment	*aux;
	char			*str_aux;
	char			*expand;
	
	str_aux = get_expand(str);
	aux  = *my_env;	
	expand = NULL;
	while (aux->next)
	{	
		if (ft_strncmp(aux->env_var, str_aux, ft_point_strchr(str_aux, '=')) == 0)
		{
			expand = ft_strdup(&aux->env_var[ft_strlen(str_aux) + 1]);
			free(str_aux);
			break ;
		}
		aux = aux ->next;
	}
	return (expand);
}
int check_if_quote(char chr, int **flag)
{
	if (chr == '"'  && *flag[P_QUOTE] == 0 && *flag[S_QUOTE] == 0)
		(*flag[P_QUOTE])++;
	else if (chr == '"'  && *flag[P_QUOTE]== 1)
	{
		(*flag[P_QUOTE])--;
		return (2);
	}
	if (chr == '\''  && *flag[S_QUOTE] == 0 && *flag[P_QUOTE] == 0)
		(*flag[S_QUOTE])++;
	else if (chr == '\''  && *flag[S_QUOTE] == 1)
	{
		(*flag[S_QUOTE])--;
		return (2);
	}
	return (0);
}

void init_lenght_vars(int **flag, int *count, int *len)
{
	*flag = (int *)malloc(2 * sizeof(int));
	*flag[0] = 0;
	*flag[1] = 0;
	*len = 0;
	*count  = 0;
	//dprintf(2, "ENTREE");
}


void	cpy_if_pair_quote(t_enviroment **myenv, char *str, int **count, char **line)
{
	char *expand;
	char *line_point;
	
	(*count[IT_STR])++;
	while (str[*count[IT_STR]] != '"' && str[*count[IT_STR]])
	{
		if (str[*count[IT_STR]] == '$')
		{
			expand = find_path_expand(myenv, &str[*count[IT_STR] + 1]);
			if (expand != NULL)
			{
				line_point = &(*line[*count[IT_LINE]]);
				ft_memcpy(line_point, expand, ft_strlen(expand));
				*count[IT_LINE] += ft_strlen(expand) + 1;
			}
			count[IT_STR] += move_along_iterator(&str[*count[IT_STR]]);
			free(expand);
		}
		*line[*count[IT_LINE]] = str[*count[IT_STR]];
		(*count[IT_STR])++;
		(*count[IT_LINE])++;
	}
}

void cpy_if_single_quote(char *str, int **count, char **line)
{
	(*count[IT_STR])++;
	while (str[*count[IT_STR]] != '\'' && str[*count[IT_STR]])
	{
		*line[*count[IT_LINE]] = str[*count[IT_STR]];
		(*count[IT_LINE])++;
		(*count[IT_STR])++;
	}
}

void init_parse_vars(int **flag, int **count)
{
	*flag = malloc(sizeof(int) * 2);
	*count = malloc(sizeof(int) * 2);
	*flag[P_QUOTE] = 0;;
	*flag[S_QUOTE] = 0;
	*count[IT_STR] = 0;
	*count[IT_LINE] = 0;
}

int len_before_pipe(t_enviroment **myenv,char *str)
{
	int		count;
	char	*expand;
	int		*flag;
	int 	len;
	
	init_lenght_vars(&flag, &count, &len);
	dprintf(2, "flag  %d\n", flag[0]);
	/*while(str[count])
	{
		if (flag[P_QUOTE] == 1 && str[count] == '$')
		{
			expand  = find_path_expand(myenv,&str[count + 1]);
			len += ft_strlen(expand);
			count+= move_along_iterator(&str[count]);
			free(expand);
		}
		len -= check_if_quote(str[count], &flag);
		if (str[count] == '|' && flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0)
			break;
		count++;
		len++;
	}
	free(flag);*/
	return(len);
}

char 	*filtered_cmd(t_enviroment **myenv, char *str)
{
	char	*line;
	int		*flag;
	int		count;

	
	count =len_before_pipe(myenv, str);
	line = NULL;
	//printf("LENNN %d\n", count);
	//init_parse_vars(&flag, &count);
	/*while(str[count[IT_STR]])	
	{
		if(flag[P_QUOTE] == 1)
			cpy_if_pair_quote(myenv, str, &count, &line);
		else if (flag[S_QUOTE] == 1)
			cpy_if_single_quote(str, &count, &line);
		check_if_quote(str[count[IT_STR]], &flag);
		if (str[count[IT_STR]] == '|' && flag[P_QUOTE] == 0 && flag[S_QUOTE] == 0)
			break;
		line[IT_LINE] = str[IT_STR];
		count[IT_STR]++;
		count[IT_LINE]++;
	}
	free(flag);
	free(count);*/
	return(line);
}
