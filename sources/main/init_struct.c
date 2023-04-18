/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:07:45 by byanis            #+#    #+#             */
/*   Updated: 2023/04/18 14:06:00 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* La fonction delete_first_node_redi permet de supprimer le premier élément
de la liste chaînée redi d'une structure t_board en passant
l'adresse de la structure cmd. Cette fonction est utilisée pour libérer
la mémoire allouée à la liste chaînée de redirections dans le cas où l'exécution
de la commande échoue. */

void	delete_first_node_redi(t_board *cmd)
{
	t_redi	*ptr;

	ptr = cmd->redi;
	if (!ptr)
		return ;
	if (ptr->next)
		cmd->redi = ptr->next;
	else
		cmd->redi = NULL;
	if (ptr->file)
		free(ptr->file);
	ptr->file = NULL;
	ptr->next = NULL;
	free(ptr);
	ptr = NULL;
}

/* La fonction free_redi permet de libérer la mémoire allouée aux listes
chaînées de redirections pour toutes les commandes dans la structure t_data
passée en paramètre.
Elle parcourt toutes les commandes stockées dans minis->cmd et,
si une commande a des redirections, elle utilise delete_first_node_redi pour
supprimer tous les nœuds de la liste chaînée de redirections. */

void	free_redi(t_data *minis)
{
	int	i;

	i = 0;
	while (i < minis->nb_cmd)
	{
		if (minis->cmd[i].redi != NULL)
		{
			while (minis->cmd[i].redi)
				delete_first_node_redi(&minis->cmd[i]);
		}
		i++;
	}
}

/* La fonction free_struct permet de libérer la mémoire allouée
pour les champs de la structure t_data passée en paramètre.
Elle utilise la fonction free_redi pour libérer la mémoire allouée aux listes
chaînées de redirections pour chaque commande et utilise également la
fonction free_struct_cmd pour libérer la mémoire allouée aux champs line_cmd
et cmd_path de chaque commande. Enfin, elle libère la mémoire allouée pour
le champ line de la structure. */

void	free_struct(t_data *minis)
{
	free_redi(minis);
	free_struct_cmd(minis);
	free(minis->line);
}

/* La fonction init_struct permet d'initialiser la structure t_data passée
en paramètre en allouant de la mémoire pour le tableau cmd et les champs
line_cmd pour chaque commande.
Elle utilise la variable minis->nb_cmd pour déterminer la taille du
tableau cmd et alloue de la mémoire pour chaque champ line_cmd en copiant
la chaîne de caractères correspondante depuis minis->tab_cmd.
Enfin, elle libère la mémoire allouée pour minis->tab_cmd. */

void	init_struct(t_data *minis)
{
	int	i;

	minis->cmd = malloc(sizeof(t_board) * minis->nb_cmd);
	if (!minis->cmd)
		ft_error("Malloc", minis, 1, 1);
	i = 0;
	while (i < minis->nb_cmd)
	{
		minis->cmd[i].line_cmd = ft_strdup(minis->tab_cmd[i]);
		if (!minis->cmd[i].line_cmd)
			ft_error("Malloc", minis, 2, 1);
		minis->cmd[i].cmd_path = NULL;
		i++;
	}
	free_tab(minis->tab_cmd, minis->nb_cmd + 1);
}
