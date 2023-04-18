/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:07:39 by byanis            #+#    #+#             */
/*   Updated: 2023/04/18 14:16:17 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* La fonction put_res_pipe permet de mettre à jour la variable
d'environnement $? avec la valeur de retour d'une commande
exécutée précédemment. Elle prend en entrée un pointeur vers la structure
t_data et un entier res qui représente la valeur de retour de la commande.
Elle commence par chercher la variable d'environnement $? à l'aide de la
fonction lst_name_finding qui parcourt la liste chaînée de variables
d'environnement jusqu'à trouver celle qui a pour nom "?". Ensuite,
elle convertit la valeur de retour en chaîne de caractères à l'aide
de la fonction ft_itoa et stocke la nouvelle valeur dans la variable trouvée.
Elle libère ensuite la chaîne de caractères convertie. */

void	put_res_pipe(t_data *minis, int res)
{
	t_var	*ptr;
	char	*new_value;

	ptr = lst_name_finding(minis->env, "?");
	new_value = ft_itoa(res);
	if (!new_value)
		ft_error("Malloc", minis, 3, 1);
	free(ptr->value);
	ptr->value = ft_strdup(new_value);
	if (!ptr->value)
	{
		free(new_value);
		ft_error("Malloc", minis, 3, 1);
	}
	free(new_value);
}

/* La fonction lst_name_finding permet de trouver un élément dans une
liste chaînée de variables d'environnement en fonction de son nom.
Elle prend en entrée un pointeur vers la liste chaînée lst et une chaîne
de caractères name qui représente le nom de la variable d'environnement
à trouver. Elle parcourt la liste chaînée jusqu'à trouver l'élément
qui a le même nom que name à l'aide d'une boucle while.
Si elle trouve l'élément, elle retourne un pointeur vers celui-ci,
sinon elle retourne NULL. */

t_var	*lst_name_finding(t_var *lst, char *name)
{
	while (lst->next != NULL && ft_strcmp(lst->name, name) != 0)
		lst = lst->next;
	if (ft_strcmp(lst->name, name) == 0)
		return (lst);
	else
		return (NULL);
}

/* La fonction lst_last permet de trouver le dernier élément d'une
liste chaînée de variables d'environnement.
Elle prend en entrée un pointeur vers la liste chaînée lst.
Elle parcourt la liste chaînée jusqu'à trouver le dernier élément à
l'aide d'une boucle while et retourne un pointeur vers celui-ci. */

t_var	*lst_last(t_var *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/* La fonction lst_add permet d'ajouter un nouvel élément à une
liste chaînée de variables d'environnement.
Elle prend en entrée un double pointeur vers la liste chaînée lst
et un pointeur vers le nouvel élément new.
Si la liste chaînée est vide, elle ajoute le nouvel élément
au début de la liste.
Sinon, elle parcourt la liste chaînée jusqu'à trouver le dernier
élément à l'aide de la fonction lst_last et ajoute le nouvel
élément à la fin de la liste. */

void	lst_add(t_var **lst, t_var *new)
{
	t_var	*aux_lst;

	if (new)
	{
		if (!*lst)
		{
			*lst = new;
			return ;
		}
		aux_lst = lst_last(*lst);
		aux_lst->next = new;
	}
}

/* La fonction ft_malloc_empty permet d'allouer de la mémoire
pour la valeur d'une variable d'environnement lorsqu'elle est
initialisée à une chaîne de caractères vide.
Elle prend en entrée un pointeur vers la structure t_data et
un pointeur vers la variable d'environnement ptr.
Elle alloue de la mémoire pour une chaîne de caractères vide
de taille 1 à l'aide de malloc et stocke un pointeur vers
cette chaîne dans ptr->value. */

void	ft_malloc_empty(t_data *minis, t_var *ptr)
{
	ptr->value = malloc(sizeof(char) * 1);
	if (!ptr->value)
		ft_error("Malloc", minis, 3, 1);
	ptr->value[0] = '\0';
}
