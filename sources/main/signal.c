/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:07:56 by byanis            #+#    #+#             */
/*   Updated: 2023/04/18 13:29:14 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* initialise les signaux pour le shell principal.
Elle ignore le signal SIGQUIT et définit le signal SIGINT pour appeler
la fonction signal_handler en cas d'interruption. Cette fonction met également
la variable globale g_code_erreur à 1 pour indiquer une erreur. */

void	init_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
}

/* signal_handler est appelée en cas d'interruption SIGINT (générée par Ctrl+C).
Elle modifie la valeur de la variable globale g_code_erreur à 1 pour indiquer
une erreur.
Elle efface également la ligne actuelle et affiche un nouveau prompt. */

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_code_erreur = 1;
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

/* line_empty est appelée lorsque l'utilisateur entre une ligne vide.
Elle libère la mémoire allouée pour la liste d'environnement env et efface
l'historique des commandes. Si l'erreur est due à un manque de mémoire,
elle affiche un message d'erreur. Elle affiche également "exit" et quitte
le programme avec le code d'erreur stocké dans la variable globale. */

void	line_empty(t_data *minis)
{
	free_list(minis->env);
	rl_clear_history();
	if (errno == ENOMEM)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
	ft_putstr_fd("exit\n", 1);
	exit(g_code_erreur);
}

/* init_signals_child initialise les signaux pour les processus fils.
Elle définit le signal SIGQUIT pour appeler la fonction signal_handler_child
en cas d'interruption SIGQUIT (générée par Ctrl+) et définit également
le signal SIGINT pour appeler la fonction signal_handler_child en cas
d'interruption SIGINT (générée par Ctrl+C). */

void	init_signals_child(void)
{
	signal(SIGQUIT, signal_handler_child);
	signal(SIGINT, signal_handler_child);
}

/* ignal_handler_child est appelée en cas d'interruption SIGINT ou SIGQUIT
pour les processus fils. Si le signal est SIGINT,
elle efface la ligne actuelle et affiche un nouveau prompt.
Si le signal est SIGQUIT,
elle efface la ligne actuelle et affiche "Quit: 3". */

void	signal_handler_child(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	if (sig == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putstr_fd("Quit: 3\n", 1);
	}
}
