/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   each_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:08:24 by byanis            #+#    #+#             */
/*   Updated: 2023/04/18 16:27:53 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* La fonction is_empty permet de vérifier si une chaîne de caractères ne
contient que des espaces ou pas. Elle prend en entrée une chaîne de caractères
str et retourne le nombre de caractères différents de l'espace
dans cette chaîne. Si ce nombre est égal à 0, cela signifie que la chaîne
ne contient que des espaces, et donc que la commande est vide. */

int	is_empty(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			count++;
		i++;
	}
	return (count);
}

/* La fonction just_one_cmd permet d'exécuter une commande unique qui ne
nécessite pas d'utilisation de pipes. Elle prend en entrée un pointeur
vers la structure t_data minis, un pointeur vers la structure t_board cmd
contenant les informations sur la commande à exécuter, et le tableau envp
contenant les variables d'environnement.
La fonction commence par vérifier s'il y a une
erreur dans les redirections de la commande en appelant la
fonction infile_error_message. Si c'est le cas, elle retourne 1.
Ensuite, elle vérifie si la commande est une commande interne en appelant la
fonction ft_is_not_fork. Si c'est le cas, elle exécute la commande interne en
appelant la fonction builtins_without_fork et retourne 0.
Sinon, elle crée un nouveau processus en appelant fork() et exécute la
commande dans le processus fils en appelant la fonction fork_one_cmd.
Elle attend ensuite la fin du processus fils avec waitpid et retourne
le code de retour de la commande. */

int	just_one_cmd(t_data *minis, t_board *cmd, char **envp)
{
	int	redi_pipe[2][2];
	int	res;

	if (!infile_error_message(&minis->cmd[0], 1))
		return (1);
	if (ft_is_not_fork(cmd))
	{
		butiltins_without_fork(minis, cmd, 0);
		return (0);
	}
	ft_pipe_redi(minis, redi_pipe);
	init_signals_child();
	cmd->res_fork = fork();
	if (cmd->res_fork < 0)
		ft_error_fork(minis, redi_pipe, 0);
	if (cmd->res_fork == 0)
		fork_one_cmd(minis, envp, redi_pipe, cmd);
	close_redi_pipe(redi_pipe);
	waitpid(minis->cmd[0].res_fork, &res, 0);
	return (res);
}

/* Les fonctions first_cmd, middle_cmd et last_cmd sont des
fonctions auxiliaires qui permettent d'exécuter une commande qui
est la première, une commande qui est au milieu ou une commande
qui est la dernière dans une série de commandes liées par des pipes.
Elles prennent en entrée un pointeur vers la structure t_data minis,
le tableau envp contenant les variables d'environnement,
et un entier i qui indique l'indice de la commande à exécuter dans
la structure t_data.
Elles commencent par récupérer un pointeur vers la structure t_board
de la commande à exécuter.
Ensuite, elles vérifient s'il y a une erreur dans les redirections de
la commande en appelant la fonction error_or_not_fork,
et si c'est le cas, elles retournent.
Sinon, elles créent un nouveau processus en appelant fork() et exécutent
la commande dans le processus fils en appelant la fonction correspondante
(fork_first_cmd, fork_middle_cmd ou fork_last_cmd).
Elles attendent ensuite la fin du processus fils avec waitpid. */

void	first_cmd(t_data *minis, char **envp, int i)
{
	t_board	*cmd;
	int		redi_pipe[2][2];

	cmd = &minis->cmd[i];
	if (error_or_not_fork(minis, cmd, 1, i))
		return ;
	ft_pipe_redi(minis, redi_pipe);
	cmd->res_fork = fork();
	if (cmd->res_fork < 0)
		ft_error_fork(minis, redi_pipe, 1);
	if (cmd->res_fork == 0)
		fork_first_cmd(minis, envp, redi_pipe, i);
	close_redi_pipe(redi_pipe);
}

void	middle_cmd(t_data *minis, char **envp, int i)
{
	t_board	*cmd;
	int		redi_pipe[2][2];

	cmd = &minis->cmd[i];
	if (error_or_not_fork(minis, cmd, 2, i))
		return ;
	ft_pipe_redi(minis, redi_pipe);
	cmd->res_fork = fork();
	if (cmd->res_fork < 0)
		ft_error_fork(minis, redi_pipe, 1);
	if (cmd->res_fork == 0)
		fork_middle_cmd(minis, envp, redi_pipe, i);
	close_redi_pipe(redi_pipe);
}

void	last_cmd(t_data *minis, char **envp, int i)
{
	t_board	*cmd;
	int		redi_pipe[2][2];

	cmd = &minis->cmd[i];
	if (error_or_not_fork(minis, cmd, 3, i))
		return ;
	ft_pipe_redi(minis, redi_pipe);
	cmd->res_fork = fork();
	if (cmd->res_fork < 0)
		ft_error_fork(minis, redi_pipe, 1);
	if (cmd->res_fork == 0)
		fork_last_cmd(minis, envp, redi_pipe, i);
	close_redi_pipe(redi_pipe);
}
