/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:08:17 by byanis            #+#    #+#             */
/*   Updated: 2023/04/18 16:12:12 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* La fonction ft_count_command compte le nombre de commandes dans une chaîne
de caractères en cherchant le caractère |.
Elle renvoie le nombre de commandes. */

int	ft_count_command(char *line)
{
	int	i;
	int	count;

	if (!line)
		return (0);
	i = 0;
	count = 0;
	while (line[i])
	{
		if (is_no_open_quote(line, i) && line[i] == '|')
			count++;
		i++;
	}
	return (count + 1);
}

/* La fonction str_cpy_cmd copie une commande à partir de la chaîne de
caractères donnée en argument jusqu'à rencontrer le caractère |.
Elle alloue dynamiquement une nouvelle chaîne de caractères pour stocker
la commande et renvoie un pointeur vers cette chaîne. */

char	*str_cpy_cmd(char *line, int *i, t_data *minis)
{
	char	*new;
	int		j;
	int		k;

	j = ft_len_cmd(line);
	new = malloc(sizeof(char) * (j + 1));
	if (!new)
		ft_error("Malloc", minis, 1, 1);
	j = 0;
	k = 0;
	if (line[j] == '|')
		j++;
	while (line[j])
	{
		if (is_no_open_quote(line, j) && line[j] == '|')
			break ;
		new[k] = line[j];
		k++;
		j++;
	}
	new[k] = '\0';
	*i += j;
	return (new);
}

/* La fonction line_to_cmd divise une ligne de commande en commandes
individuelles en utilisant les fonctions ft_count_command et str_cpy_cmd.
Elle stocke les pointeurs vers les commandes dans un tableau de pointeurs de
chaînes de caractères appelé tab_cmd,
et le nombre de commandes dans une variable appelée nb_cmd. */

void	line_to_cmd(t_data *minis)
{
	int	i;
	int	nb_cmd;

	if (minis->line && *minis->line == '|')
		ft_error("Parsing error", minis, 0, 0);
	nb_cmd = ft_count_command(minis->line);
	minis->tab_cmd = malloc(sizeof(char *) * (nb_cmd + 1));
	if (!minis->tab_cmd)
		ft_error("Malloc", minis, 0, 1);
	i = 0;
	minis->nb_cmd = 0;
	while (minis->nb_cmd < nb_cmd)
	{
		minis->tab_cmd[minis->nb_cmd] = str_cpy_cmd(minis->line + i, &i, minis);
		minis->nb_cmd++;
	}
	minis->tab_cmd[minis->nb_cmd] = malloc(sizeof(char) * 1);
	if (!minis->tab_cmd[minis->nb_cmd])
		ft_error("Malloc", minis, 1, 1);
	minis->tab_cmd[minis->nb_cmd][0] = '\0';
}

/* La fonction ft_write est une fonction auxiliaire qui copie un caractère
d'une chaîne de caractères à une autre. Ell
 est utilisée pour copier les caractères qui ne sont pas des guillemets simples
 ou doubles dans la nouvelle chaîne lors de la suppression des guillemets
 dans la fonction delete_quote. */

void	ft_write(char *new, char *str, int *i, int *j)
{
	new[*j] = str[*i];
	*i += 1;
	*j += 1;
}
