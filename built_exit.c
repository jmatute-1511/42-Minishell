/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:11:49 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/24 19:31:09 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_matrixlen(char **matrix)
{
	int	a;

	a = 0;
	while (matrix[a] != NULL)
		a++;
	return (a);
}

void	more_arg_err(char **matrix)
{
	if (ft_matrixlen(matrix) > 2)
	{
		ft_putstr_fd("Myshell :exit: too many arguments", 2);
		exit(1);
	}
}

void	err_msg_arg(char *str_m, int it)
{
	char	*err_msg;

	err_msg = NULL;
	if (str_m[it] != '\0' || it > 19)
	{
		err_msg = ft_strnjoin(3, "exit: ", str_m, \
		": numeric argument required\n");
		ft_putstr_fd(err_msg, 2);
		free(err_msg);
		exit(255);
	}
}

void	built_exit(char *str, t_myvars **my_vars)
{
	int		it;
	char	*str_m;
	char	**matrix;
	int		n_atoi;

	it = 0;
	matrix = ft_split(str, ' ');
	str_m = matrix[1];
	more_arg_err(matrix);
	if (str_m == NULL)
		exit(EXIT_SUCCESS);
	if (str_m[it] == '-')
		it++;
	while (str_m[it] >= '0' && str_m[it] <= '9' && str_m)
		it++;
	err_msg_arg(str_m, it);
	n_atoi = ft_atoi(str_m);
	if (n_atoi >= 256)
		(*my_vars)->stat = n_atoi % 256;
	else
		(*my_vars)->stat = n_atoi;
	if (n_atoi < 0)
		exit(UCHAR_MAX - (*my_vars)->stat + 1);
	free_vars(my_vars);
	exit((*my_vars)->stat);
}
