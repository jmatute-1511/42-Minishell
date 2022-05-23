/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boleans_first_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:57:03 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/23 12:46:08 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int bolean_errors_quotes(char *str)
{
	int pair_quote;
	int single_quote;
	int count;
	
	count = 0;
	pair_quote = 0;
	single_quote = 0;
	while(str[count])
	{
		if (str[count] == '"' && pair_quote == 0 && single_quote == 0)
			pair_quote++;
		else if (str[count] == '"' && pair_quote == 1)
			pair_quote--;
		if (str[count] == '\''  && single_quote == 0 && pair_quote == 0)
			single_quote++;
		else if (str[count] == '\''  && single_quote == 1)
			(single_quote)--;
		count++;
	}
	if(pair_quote != 0 || single_quote != 0)
		return(1);
	return (0);
	
}

int first_filter_errors(char *str)
{
	if (bolean_errors_quotes(str))
		return(1);
	return (0);
}