/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_hdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:07:53 by byanis            #+#    #+#             */
/*   Updated: 2023/04/18 13:18:10 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* La fonction init_signals_h_doc initialise les signaux utilisés par
le programme.
Elle ignore le signal SIGQUIT et utilise la fonction signal_handler_h_doc pour
gérer le signal SIGINT. */

void	init_signals_h_doc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler_h_doc);
}

/* La fonction signal_handler_h_doc est une fonction de gestion des signaux
qui est appelée lorsqu'un signal est reçu. Elle prend en argument le numéro
du signal reçu et quitte le programme si le signal reçu est SIGINT. */

void	signal_handler_h_doc(int sig)
{
	if (sig == SIGINT)
		exit(1);
}

/* La fonction line_empty_h_doc est appelée lorsque l'utilisateur entre une
ligne vide. Elle quitte le programme en retournant le code d'erreur 0. */

void	line_empty_h_doc(void)
{
	exit(0);
}
