/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:09:13 by byanis            #+#    #+#             */
/*   Updated: 2023/04/17 23:09:13 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_to_new_quote(char *str, int *i, int quote)
{
	int	count;

	count = 0;
	*i += 1;
	while (str[*i] && str[*i] != quote)
	{
		*i += 1;
		count++;
	}
	return (count);
}

int	is_no_open_single_quote(char *line, int i)
{
	int	single_quote;
	int	double_quote;
	int	j;

	j = 0;
	single_quote = 0;
	double_quote = 0;
	while (j < i)
	{
		if (line[j] == 39 && double_quote % 2 == 0)
			single_quote++;
		if (line[j] == 34 && single_quote % 2 == 0)
			double_quote++;
		j++;
	}
	if (single_quote % 2 != 0)
		return (0);
	return (1);
}

int	is_no_open_quote(char *line, int i)
{
	int	single_quote;
	int	double_quote;
	int	j;

	j = 0;
	single_quote = 0;
	double_quote = 0;
	while (j < i)
	{
		if (line[j] == 39 && double_quote % 2 == 0)
			single_quote++;
		if (line[j] == 34 && single_quote % 2 == 0)
			double_quote++;
		j++;
	}
	if (single_quote % 2 != 0)
		return (0);
	if (double_quote % 2 != 0)
		return (0);
	return (1);
}
