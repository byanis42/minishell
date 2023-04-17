/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:07:56 by byanis            #+#    #+#             */
/*   Updated: 2023/04/17 23:07:56 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
}

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

void	init_signals_child(void)
{
	signal(SIGQUIT, signal_handler_child);
	signal(SIGINT, signal_handler_child);
}

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
