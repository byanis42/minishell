/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:08:13 by byanis            #+#    #+#             */
/*   Updated: 2023/04/18 15:58:30 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* La fonction ft_len_words prend une chaîne de caractères en entrée et
retourne la longueur du premier mot dans cette chaîne, ou la longueur totale
de la chaîne s'il n'y a pas de mot. */

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

/* La fonction ft_count_split prend une chaîne de caractères en entrée et
retourne le nombre de mots dans cette chaîne. */

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

/* La fonction str_cpy_words prend une chaîne de caractères en entrée et
une adresse de pointeur de chaîne, qui sera modifiée pour pointer sur
le caractère suivant après le mot copié.
La fonction copie le premier mot dans la chaîne, saute les espaces suivants,
met un caractère nul à la fin et retourne un pointeur vers le début
de la nouvelle chaîne allouée. */

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

/* La fonction ft_split_each_cmd prend une chaîne de caractères et
les pointeurs de la structure de commande et de la structure de shell,
puis alloue de la mémoire pour stocker les mots de la commande.
La fonction utilise str_cpy_words pour copier chaque mot dans la nouvelle
chaîne et incrémenter le pointeur de la chaîne d'entrée,
qui est ensuite stockée dans un tableau de pointeurs de chaînes.
La fonction retourne le tableau. */

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

/* La fonction ft_split_cmd utilise ft_split_each_cmd pour chaque commande
dans la structure de shell pour diviser les commandes en mots et les stocker
dans les structures de commande correspondantes. */

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
