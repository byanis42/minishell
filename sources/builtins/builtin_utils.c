/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:06:45 by byanis            #+#    #+#             */
/*   Updated: 2023/04/18 14:20:09 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Cette fonction affiche le chemin du répertoire de travail actuel à l'aide
de la fonction getcwd de la bibliothèque <unistd.h>. Si getcwd renvoie
une valeur, la fonction affiche cette valeur en utilisant ft_putendl_fd et met
le code d'erreur global à 0. Sinon, le code d'erreur global est mis à 1. */

void	ft_pwd(void)
{
	char	cwd[PATH_LEN];

	if (getcwd(cwd, PATH_LEN))
	{
		ft_putendl_fd(cwd, 1);
		g_code_erreur = 0;
		return ;
	}
	g_code_erreur = 1;
}

/* Cette fonction affiche toutes les variables d'environnement enregistrées
dans la structure minis->env en utilisant la fonction print_list et met le code
d'erreur global à 0. */

void	ft_envp(t_data *minis)
{
	print_list(minis->env, 0);
	g_code_erreur = 0;
}

/* Cette fonction vérifie si la chaîne de caractères cmd est une option pour
la commande echo. Si cmd commence par "-n" et contient seulement des "n"
ensuite, elle renvoie 1. Sinon, elle renvoie 0. */

int	check_option_echo(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '-' && cmd[i + 1] == 'n')
	{
		i++;
		while (cmd[i])
		{
			if (cmd[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

/* Cette fonction prend en entrée un pointeur vers une structure t_board
contenant les mots d'une commande echo et les affiche à l'écran.
Si l'option "-n" est passée en premier argument de la commande,
elle est prise en compte et la fin de ligne est supprimée.
Le code d'erreur global est mis à 0. */

void	ft_echo(t_board *cmd)
{
	int	i;
	int	option;

	option = 0;
	if (cmd->nb_words == 2)
	{
		ft_putchar_fd('\n', 1);
		g_code_erreur = 0;
		return ;
	}
	i = 1;
	while (i < cmd->nb_words - 1)
	{
		if (!check_option_echo(cmd->tab[i]))
			break ;
		i++;
	}
	if (i > 1)
		option = 1;
	ft_echo_bis(cmd, i, option);
}

/* Cette fonction affiche le reste des arguments de la commande echo
après avoir vérifié et traité l'option "-n" dans la fonction ft_echo.
Les arguments sont séparés par des espaces.
Si l'option "-n" n'a pas été passée, la fin de ligne est ajoutée
à la fin des arguments. Le code d'erreur global est mis à 0. */

void	ft_echo_bis(t_board *cmd, int i, int option)
{
	while (i < cmd->nb_words - 1)
	{
		ft_putstr_fd(cmd->tab[i], 1);
		if (i < cmd->nb_words - 2)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (option == 0)
		ft_putchar_fd('\n', 1);
	g_code_erreur = 0;
}
