/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:08:32 by byanis            #+#    #+#             */
/*   Updated: 2023/04/18 16:18:15 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Cette fonction est utilisée pour exécuter une commande unique
(c'est-à-dire sans pipeline).
Elle utilise les descripteurs de fichiers pour gérer les entrées/sorties
redirigées, puis appelle soit la fonction execve pour exécuter la
commande externe, soit une fonction de built-in si
la commande est un built-in. */

void	fork_one_cmd(t_data *minis, char **envp,
		int redi_pipe[2][2], t_board *cmd)
{
	if (redirect_infile(cmd, redi_pipe[0]))
		dup2(redi_pipe[0][0], 0);
	if (redirect_outfile(cmd, redi_pipe[1]))
		dup2(redi_pipe[1][1], 1);
	close_redi_pipe(redi_pipe);
	if (!ft_is_builtins(cmd))
		execve(cmd->cmd_path, cmd->tab, envp);
	builtins_with_fork(minis, cmd);
	free_struct(minis);
	free_list(minis->env);
	exit(1);
}

/* Cette fonction est utilisée pour exécuter la première commande d'un pipeline.
Elle utilise les descripteurs de fichiers pour gérer les entrées/sorties
redirigées et le pipe, puis appelle soit la fonction execve pour exécuter
la commande externe, soit une fonction de built-in si
la commande est un built-in. */

void	fork_first_cmd(t_data *minis, char **envp,
		int redi_pipe[2][2], int i)
{
	t_board	*cmd;

	cmd = &minis->cmd[i];
	if (redirect_infile(cmd, redi_pipe[0]))
		dup2(redi_pipe[0][0], 0);
	if (redirect_outfile(cmd, redi_pipe[1]))
		dup2(redi_pipe[1][1], minis->cmd[0].pipe_fd[1]);
	dup2(minis->cmd[0].pipe_fd[1], 1);
	close_all_pipes(minis);
	close_redi_pipe(redi_pipe);
	if (!ft_is_builtins(&minis->cmd[0]))
		execve(minis->cmd[0].cmd_path, minis->cmd[0].tab, envp);
	builtins_with_fork(minis, &minis->cmd[i]);
	free_struct(minis);
	free_list(minis->env);
	exit(1);
}

/* Cette fonction est utilisée pour exécuter une commande intermédiaire
d'un pipeline. Elle utilise les descripteurs de fichiers pour gérer
les entrées/sorties redirigées et le pipe, puis appelle soit la
fonction execve pour exécuter la commande externe,
soit une fonction de built-in si la commande est un built-in. */

void	fork_middle_cmd(t_data *minis, char **envp,
		int redi_pipe[2][2], int i)
{
	t_board	*cmd;

	cmd = &minis->cmd[i];
	if (redirect_infile(cmd, redi_pipe[0]))
		dup2(redi_pipe[0][0], minis->cmd[i - 1].pipe_fd[0]);
	dup2(minis->cmd[i - 1].pipe_fd[0], 0);
	if (redirect_outfile(cmd, redi_pipe[1]))
		dup2(redi_pipe[1][1], minis->cmd[i].pipe_fd[1]);
	dup2(minis->cmd[i].pipe_fd[1], 1);
	close_all_pipes(minis);
	close_redi_pipe(redi_pipe);
	if (!ft_is_builtins(&minis->cmd[i]))
		execve(minis->cmd[i].cmd_path, minis->cmd[i].tab, envp);
	builtins_with_fork(minis, &minis->cmd[i]);
	free_struct(minis);
	free_list(minis->env);
	exit(1);
}

/* Cette fonction est utilisée pour exécuter la dernière commande
d'un pipeline. Elle utilise les descripteurs de fichiers pour gérer
les entrées/sorties redirigées et le pipe, puis appelle soit la
fonction execve pour exécuter la commande externe, soit une fonction
de built-in si la commande est un built-in. */

void	fork_last_cmd(t_data *minis, char **envp,
		int redi_pipe[2][2], int i)
{
	t_board	*cmd;

	cmd = &minis->cmd[i];
	if (redirect_infile(cmd, redi_pipe[0]))
		dup2(redi_pipe[0][0], minis->cmd[i - 1].pipe_fd[0]);
	dup2(minis->cmd[i - 1].pipe_fd[0], 0);
	if (redirect_outfile(cmd, redi_pipe[1]))
		dup2(redi_pipe[1][1], 1);
	close_all_pipes(minis);
	close_redi_pipe(redi_pipe);
	if (!ft_is_builtins(&minis->cmd[i]))
		execve(minis->cmd[i].cmd_path, minis->cmd[i].tab, envp);
	builtins_with_fork(minis, &minis->cmd[i]);
	free_struct(minis);
	free_list(minis->env);
	exit(1);
}

/* Cette fonction attend que tous les processus enfants créés
par le shell aient terminé leur exécution et stocke le résultat
de chaque processus dans la variable res.
Elle utilise la fonction waitpid pour attendre
la fin de chaque processus. */

void	wait_all_pid(t_data *minis, int *res)
{
	int	i;

	i = 0;
	while (i < minis->nb_cmd)
	{
		if (!ft_is_not_fork(&minis->cmd[i])
			&& infile_error_message(&minis->cmd[i], 0))
			waitpid(minis->cmd[i].res_fork, res, 0);
		i++;
	}
}
