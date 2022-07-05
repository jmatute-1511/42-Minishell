/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bremesar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:43:58 by bremesar          #+#    #+#             */
/*   Updated: 2022/06/18 14:44:05 by bremesar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//usa el comando "bash" en la terminal para los ejemplos
//haz el de <<
void	redirect_left(char *text)
{

}

void	redirect_right(char *text)
{

}

void	redirect_leftdouble(char *text)
{
	int		filedesc;
	int		out_aux; //pipe duplicado auxiliar
	char	*str;

	filedesc = open("temp", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if (filedesc < 0)
		return ;
	out_aux = dup(1);
	while (1)
	{
		str = readline(ROJO_T">"COLOR_RESET);
		if (ft_strcmp(str, text) == 0)
		{
			dup2(out_aux, 1);
			close(filedesc);
			return;
		}
		else
		{
			dup2(filedesc, 1);
			printf("%s\n", str);
			dup2(out_aux, 1);
		}
	}
}

void	redirect_rightdouble(char *text)
{
	
}