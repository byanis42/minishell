/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:08:40 by byanis            #+#    #+#             */
/*   Updated: 2023/04/18 16:14:42 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* La fonction close_for_cmd_pipe est utilisée pour fermer les tuyaux
selon qu'il s'agit du premier, du dernier ou du tuyau intermédiaire. */

void	close_for_cmd_pipe(t_data *minis, int z, int i)
{
	if (z == 1)
		close(minis->cmd[0].pipe_fd[1]);
	if (z == 2)
	{
		close(minis->cmd[i - 1].pipe_fd[0]);
		close(minis->cmd[i].pipe_fd[1]);
	}
	if (z == 3)
		close(minis->cmd[i - 1].pipe_fd[0]);
}

/* La fonction error_or_not_fork vérifie si la commande actuelle a échoué et
s'il ne s'agit pas d'une commande intégrée.
Si c'est le cas, les tuyaux sont fermés et la fonction renvoie 1 pour
indiquer qu'une erreur s'est produite. */

int	error_or_not_fork(t_data *minis, t_board *cmd, int z, int i)
{
	if (!infile_error_message(&minis->cmd[i], 1))
	{
		close_for_cmd_pipe(minis, z, i);
		return (1);
	}
	if (ft_is_not_fork(cmd))
	{
		close_for_cmd_pipe(minis, z, i);
		butiltins_without_fork(minis, cmd, i);
		return (1);
	}
	return (0);
}

/* La fonction command_error_message parcourt toutes les commandes et vérifie
si elles ont échoué, n'ont pas été trouvées ou si leur chemin
d'accès n'est pas valide. Si l'un de ces cas est vérifié,
un message d'erreur est affiché à l'écran. */

void	command_error_message(t_data *minis, int print)
{
	t_board	*cmd;
	int		i;

	i = 0;
	while (i < minis->nb_cmd)
	{
		cmd = &minis->cmd[i];
		if ((!cmd->cmd_path && !ft_is_builtins(cmd))
			|| (cmd->tab[0][0] == '\0'))
		{
			if (print == 1 && !is_redi_infile(minis->cmd[i].redi)
				&& cmd->var_env_empty != 1
				&& !is_redi_outfile(minis->cmd[i].redi))
			{
				ft_putstr_fd("Command not found :", 2);
				ft_putstr_fd(cmd->tab[0], 2);
				ft_putchar_fd('\n', 2);
			}
		}
		i++;
	}
}

/* La fonction check_acces_read vérifie si le fichier est accessible en lecture.
Si l'ouverture du fichier échoue, la fonction renvoie 0. */

int	check_acces_read(t_redi *ptr, int print)
{
	if (access(ptr->file, R_OK) != 0)
	{
		if (print == 1)
		{
			ft_putstr_fd("Error to open file :", 2);
			ft_putstr_fd(ptr->file, 2);
			ft_putchar_fd('\n', 2);
		}
		return (0);
	}
	return (1);
}

/* La fonction infile_error_message est utilisée pour vérifier si l'entrée
standard d'une commande a été correctement redirigée.
Si ce n'est pas le cas, un message d'erreur est affiché et la fonction renvoie 0.
Si tout se passe bien, la fonction renvoie 1. */

int	infile_error_message(t_board *cmd, int print)
{
	t_redi	*ptr;

	ptr = cmd->redi;
	if (!ptr)
		return (1);
	while (ptr->next != NULL)
	{
		if (ptr->type == INFILE)
			if (!check_acces_read(ptr, print))
				return (0);
		ptr = ptr->next;
	}
	if (ptr->type == INFILE)
		if (!check_acces_read(ptr, print))
			return (0);
	return (1);
}
