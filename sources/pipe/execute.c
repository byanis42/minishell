/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:08:28 by byanis            #+#    #+#             */
/*   Updated: 2023/04/18 16:19:29 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Cette fonction ferme tous les descripteurs de fichiers associés aux pipes.
Elle prend en argument une structure t_data qui contient toutes les informations
nécessaires pour gérer les pipes. */

void	ft_execute_bis(t_data *minis, char **envp, int i)
{
	if (i == 0)
		first_cmd(minis, envp, i);
	else if (i == minis->nb_cmd - 1)
	{
		if (is_redi_d_infile(minis->cmd[i - 1].redi))
			wait(NULL);
		last_cmd(minis, envp, i);
	}
	else
	{
		if (is_redi_d_infile(minis->cmd[i - 1].redi))
			wait(NULL);
		middle_cmd(minis, envp, i);
	}
}

/* Cette fonction parcourt toutes les commandes et vérifie si elles font
partie des built-ins. Si ce n'est pas le cas, elle recherche
le chemin absolu de l'exécutable en utilisant la variable d'environnement PATH.
Elle met à jour la structure de la commande avec le chemin absolu.
Elle prend en argument une structure t_data qui contient toutes les
informations nécessaires pour gérer les commandes. */

int	ft_execute(t_data *minis, char **envp)
{
	int	i;
	int	res;

	init_signals_child();
	i = 0;
	while (i < minis->nb_cmd)
	{
		ft_execute_bis(minis, envp, i);
		i++;
	}
	close_all_pipes(minis);
	wait_all_pid(minis, &res);
	if (!minis->cmd[minis->nb_cmd - 1].cmd_path
		&& !ft_is_builtins(&minis->cmd[minis->nb_cmd - 1]))
		return (127);
	return (res);
}
