/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:08:44 by byanis            #+#    #+#             */
/*   Updated: 2023/04/18 16:05:59 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* La fonction close_all_pipes() ferme tous les descripteurs de fichier
associés aux pipes pour chaque commande dans minis->cmd.
Pour cela, elle boucle sur chaque commande et ferme les deux extrémités de
chaque pipe créé en appelant la fonction close(). */

void	close_all_pipes(t_data *minis)
{
	int	i;

	i = 0;
	while (i < minis->nb_cmd - 1)
	{
		close(minis->cmd[i].pipe_fd[0]);
		close(minis->cmd[i].pipe_fd[1]);
		i++;
	}
}

/* La fonction find_path_struct() cherche la variable d'environnement PATH
en appelant la fonction list_chr() qui recherche la variable dans la liste
chaînée minis->env.
Elle boucle ensuite sur chaque commande stockée dans minis->cmd et vérifie si
elle n'est pas une commande interne en appelant la fonction ft_is_builtins().
Si la commande n'est pas interne et que son premier argument existe,
elle appelle la fonction ft_try_path() qui tente de trouver le chemin absolu
de l'exécutable en utilisant la variable PATH et en combinant les éléments de
la chaîne minis->cmd[i].tab[0] qui contient le nom de la commande avec les
différents chemins de la variable PATH.
Le chemin absolu est ensuite stocké dans minis->cmd[i].cmd_path. */

void	find_path_struct(t_data *minis)
{
	char	*path;
	int		i;

	i = 0;
	path = list_chr(minis->env, "PATH");
	while (i < minis->nb_cmd)
	{
		if (!ft_is_builtins(&minis->cmd[i]))
		{
			if (!minis->cmd[i].tab[0] || minis->cmd[i].tab[0][0] == '\0')
			{
				i++;
				continue ;
			}
			minis->cmd[i].cmd_path = ft_try_path(minis, path, &minis->cmd[i]);
		}
		i++;
	}
	return ;
}

/* La fonction create_pipe() crée un pipe entre chaque paire de commandes
dans minis->cmd en bouclant sur chaque commande jusqu'à minis->nb_cmd - 1.
Pour chaque commande, elle appelle la fonction pipe() pour créer
un nouveau pipe,
en stockant les deux extrémités dans minis->cmd[i].pipe_fd. */

void	create_pipe(t_data *minis)
{
	int	i;

	i = 0;
	while (i < minis->nb_cmd - 1)
	{
		if (pipe(minis->cmd[i].pipe_fd) == -1)
			ft_error_to_pipe(minis, i);
		i++;
	}
}

/* La fonction ft_pipe() gère l'exécution d'un ou plusieurs processus
liés par des pipes. Elle appelle d'abord find_path_struct() pour trouver
le chemin absolu de chaque commande externe qui se trouve dans minis->cmd.
Si le nombre de commandes est égal à 1, elle appelle simplement la
fonction just_one_cmd() pour exécuter la commande unique,
sinon elle crée des pipes pour chaque paire de commandes en appelant
create_pipe(), puis exécute les commandes avec la fonction ft_execute().
Enfin, elle renvoie le code de retour de la dernière commande exécutée,
en le transformant éventuellement en code de retour de statut de processus
si c'est nécessaire
(par exemple, si la commande renvoie un code de retour entre 2 et 31,
on ajoute 128 à ce code pour obtenir le code de statut de processus).
Si la dernière commande est une commande interne, elle retourne 0,
sinon si elle ne peut pas trouver le chemin absolu de la dernière commande
externe, elle renvoie 127. */

int	ft_pipe(t_data *minis, char **envp)
{
	int	res;

	find_path_struct(minis);
	if (minis->nb_cmd == 1)
		res = just_one_cmd(minis, &minis->cmd[0], envp);
	else
	{
		create_pipe(minis);
		res = ft_execute(minis, envp);
	}
	if (res >= 2 && res <= 31)
		return (res + 128);
	if (res % 256 == 0)
		res /= 256;
	if (!ft_is_not_fork(&minis->cmd[minis->nb_cmd - 1])
		&& ft_is_builtins(&minis->cmd[minis->nb_cmd - 1]))
		res = 0;
	if (!minis->cmd[minis->nb_cmd - 1].cmd_path
		&& !ft_is_builtins(&minis->cmd[minis->nb_cmd - 1]))
		return (127);
	return (res);
}
