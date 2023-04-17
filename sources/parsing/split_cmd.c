/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:08:13 by byanis            #+#    #+#             */
/*   Updated: 2023/04/17 23:08:13 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_len_words(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] && line[i] == ' ')
		line++;
	while (line[i])
	{
		if (is_no_open_quote(line, i) && line[i] == ' ')
			return (i);
		i++;
	}
	return (i);
}

int	ft_count_split(char *line)
{
	int	i;
	int	count;

	if (!line)
		return (0);
	i = 0;
	count = 0;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i])
	{
		if (is_no_open_quote(line, i) && line[i] != ' ')
		{
			count++;
			while (line[i] && line[i] != ' ')
				i++;
			continue ;
		}
		i++;
	}
	return (count);
}

char	*str_cpy_words(char *line, int *i)
{
	char	*new;
	int		j;
	int		k;

	j = ft_len_words(line);
	new = malloc(sizeof(char) * (j + 1));
	if (!new)
		return (NULL);
	j = 0;
	k = 0;
	while (line[j] == ' ')
		j++;
	while (line[j])
	{
		if (is_no_open_quote(line, j) && line[j] == ' ')
			break ;
		new[k] = line[j];
		k++;
		j++;
	}
	new[k] = '\0';
	while (line[j] == ' ')
		j++;
	*i += j;
	return (new);
}

char	**ft_split_each_cmd(char *str, t_board *cmd, t_data *minis)
{
	int		i;
	int		j;
	char	**tab;

	i = ft_count_split(str) + 1;
	tab = malloc(sizeof(char *) * (i));
	if (!tab)
		ft_error("Malloc", minis, 3, 1);
	j = 0;
	i = 0;
	cmd->nb_words = 0;
	while (str[i])
	{
		tab[j] = str_cpy_words(str + i, &i);
		if (!tab[j])
		{
			free_tab(tab, j);
			ft_error("Malloc", minis, 3, 1);
		}
		j++;
		cmd->nb_words++;
	}
	tab[j] = NULL;
	cmd->nb_words++;
	return (tab);
}

void	ft_split_cmd(t_data *minis)
{
	int	i;

	i = 0;
	while (i < minis->nb_cmd)
	{
		minis->cmd[i].tab = ft_split_each_cmd(minis->cmd[i].line_cmd,
				&minis->cmd[i], minis);
		i++;
	}
}
