/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:07:14 by byanis            #+#    #+#             */
/*   Updated: 2023/04/18 15:36:34 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* La fonction ft_is_digital permet de vérifier si une chaîne de caractères
ne contient que des chiffres. Elle renvoie 1 si c'est le cas,
et affiche un message d'erreur et renvoie 0 sinon. */

int	ft_is_digital(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_putstr_fd("numeric argument required\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

/* Cette fonction libère la mémoire allouée pour les structures
utilisées par le shell, en appelant free_struct pour libérer la mémoire allouée
pour la structure t_data et free_list pour libérer la mémoire allouée pour la
liste chaînée des variables d'environnement. */

void	ft_free_exit(t_data *minis)
{
	free_struct(minis);
	free_list(minis->env);
}

/* Cette fonction est appelée lorsque l'utilisateur entre la commande exit.
Si elle est appelée avec un ou deux arguments, elle interprète le premier
argument comme le code de sortie à utiliser. Si l'argument n'est pas un nombre,
elle utilise le code de sortie 255.
Sinon, elle utilise l'argument comme code de sortie.
La fonction libère ensuite la mémoire utilisée par le shell
et quitte le programme en appelant exit. */

void	ft_exit(t_data *minis, t_board *cmd)
{
	int	exit_code;
	int	i;

	i = 0;
	ft_putstr_fd("exit\n", 1);
	if (cmd->nb_words > 3)
	{
		ft_putstr_fd("too much argument for exit\n", 2);
		g_code_erreur = 1;
		return ;
	}
	if (cmd->nb_words == 3)
	{
		if (cmd->tab[1][0] == '-')
			i++;
		if (!ft_is_digital(cmd->tab[1] + i))
			exit_code = 255;
		else
			exit_code = ft_atoi(cmd->tab[1]);
	}
	else
		exit_code = 0;
	rl_clear_history();
	ft_free_exit(minis);
	exit(exit_code);
}

/* Cette fonction est appelée lorsque le shell est en mode forké
(c'est-à-dire qu'il a créé un processus fils pour exécuter une commande).
Elle appelle les fonctions correspondant aux commandes internes telles
que pwd, cd, echo, exit, export et unset. */

void	builtins_with_fork(t_data *minis, t_board *cmd)
{
	if (ft_strcmp(cmd->tab[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->tab[0], "env") == 0)
		ft_envp(minis);
	else if (ft_strcmp(cmd->tab[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->tab[0], "exit") == 0)
		ft_exit(minis, cmd);
	else if (ft_strcmp(cmd->tab[0], "cd") == 0)
		ft_cd(minis, cmd);
	else if (ft_strcmp(cmd->tab[0], "export") == 0)
		ft_export(minis, cmd);
	else if (ft_strcmp(cmd->tab[0], "unset") == 0)
		ft_unset(minis, cmd);
}

/* Cette fonction est appelée lorsque le shell est en mode non forké
(c'est-à-dire qu'il n'a pas créé de processus fils pour exécuter une commande).
Elle appelle les fonctions correspondant aux commandes internes
telles que cd, exit, export et unset.
Notez que pwd et echo ne sont pas appelés dans ce mode
car ils ne sont pas compatibles avec la redirection. */

void	butiltins_without_fork(t_data *minis, t_board *cmd, int i)
{
	if (minis->nb_cmd != 1 && i != (minis->nb_cmd - 1))
		return ;
	if (ft_strcmp(cmd->tab[0], "exit") == 0)
		ft_exit(minis, cmd);
	else if (ft_strcmp(cmd->tab[0], "cd") == 0)
		ft_cd(minis, cmd);
	else if (ft_strcmp(cmd->tab[0], "export") == 0 && cmd->nb_words > 2)
		ft_export(minis, cmd);
	else if (ft_strcmp(cmd->tab[0], "unset") == 0)
		ft_unset(minis, cmd);
}
