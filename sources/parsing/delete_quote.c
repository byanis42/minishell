/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:06:32 by byanis            #+#    #+#             */
/*   Updated: 2023/04/18 16:13:44 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* La fonction count_new_quote compte le nombre de caractères dans une chaîne
de caractères en prenant en compte les quotes simples (') et doubles ("). */

int	count_new_quote(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == 39)
			count += count_to_new_quote(str, &i, 39);
		else if (str[i] == 34)
			count += count_to_new_quote(str, &i, 34);
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

/* La fonction write_to_new_singlequote et write_to_new_doublequote permettent
d'écrire une partie de la chaîne de caractères str (entre quotes) dans
la nouvelle chaîne de caractères new.
La variable i représente la position actuelle dans la chaîne de caractères str
et la variable j représente la position actuelle dans la nouvelle chaîne
de caractères new. */

void	write_to_new_singlequote(char *str, char *new, int *i, int *j)
{
	*i += 1;
	while (str[*i] && str[*i] != 39)
	{
		new[*j] = str[*i];
		*i += 1;
		*j += 1;
	}
	if (str[*i] == 39)
		*i += 1;
}

void	write_to_new_doublequote(char *str, char *new, int *i, int *j)
{
	*i += 1;
	while (str[*i] && str[*i] != 34)
	{
		new[*j] = str[*i];
		*i += 1;
		*j += 1;
	}
	if (str[*i] == 34)
		*i += 1;
}

/* La fonction get_new_str crée une nouvelle chaîne de caractères
en enlevant les quotes simples et doubles de la chaîne de caractères str.
Elle utilise les fonctions
write_to_new_singlequote et write_to_new_doublequote. */

char	*get_new_str(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = count_new_quote(str);
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == 39)
			write_to_new_singlequote(str, new, &i, &j);
		else if (str[i] == 34)
			write_to_new_doublequote(str, new, &i, &j);
		else
			ft_write(new, str, &i, &j);
	}
	new[j] = '\0';
	free(str);
	return (new);
}

/* La fonction delete_quote permet de supprimer les quotes dans les
commandes stockées dans la structure t_cmd du programme.
Elle utilise la fonction get_new_str pour chaque mot des commandes. */

void	delete_quote(t_data *minis)
{
	int	i;
	int	j;

	i = 0;
	while (i < minis->nb_cmd)
	{
		j = 0;
		while (j < minis->cmd[i].nb_words - 1)
		{
			minis->cmd[i].tab[j] = get_new_str(minis->cmd[i].tab[j]);
			if (!minis->cmd[i].tab[j])
				ft_error("Malloc", minis, 2, 1);
			j++;
		}
		i++;
	}
}
