/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:08:05 by byanis            #+#    #+#             */
/*   Updated: 2023/04/18 15:55:10 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Cette fonction vérifie si l'argument de la commande est un répertoire.
Si c'est le cas, elle affiche un message d'erreur et renvoie 1.
Sinon, elle renvoie 0. */

int	error_message_directory(t_data *minis, t_board *cmd, int i)
{
	int		j;

	j = 0;
	if (!cmd->tab[0] || !*cmd->tab[0])
		return (0);
	j = ft_strlen(cmd->tab[0]) - 1;
	if (j >= 2 && access_check(cmd->tab[0]) && (cmd->tab[0][j] == '/'
		|| (cmd->tab[0][0] == '.' || cmd->tab[0][1] == '/')))
	{
		ft_putstr_fd(cmd->tab[0], 2);
		ft_putstr_fd(": is a directory\n", 2);
		if (i == minis->nb_cmd - 1)
			g_code_erreur = 126;
		return (1);
	}
	return (0);
}

/* Cette fonction parcourt toutes les commandes dans la structure minis et
utilise la fonction error_message_directory pour chaque commande.
Si une commande est un répertoire, elle affiche un message d'erreur. */

void	check_directory(t_data *minis)
{
	int	i;

	i = 0;
	while (i < minis->nb_cmd)
	{
		if (!error_message_directory(minis, &minis->cmd[i], i))
			command_error_message(minis, 1);
		i++;
	}
}
