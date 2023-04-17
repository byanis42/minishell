/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_hdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:07:53 by byanis            #+#    #+#             */
/*   Updated: 2023/04/17 23:07:53 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_signals_h_doc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler_h_doc);
}

void	signal_handler_h_doc(int sig)
{
	if (sig == SIGINT)
		exit(1);
}

void	line_empty_h_doc(void)
{
	exit(0);
}
