/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:09:30 by byanis            #+#    #+#             */
/*   Updated: 2023/04/17 23:09:30 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error(char *message, t_data *minis, int z, int is_perror)
{
	if (z >= 0)
		free_list(minis->env);
	if (z > 0)
	{
		rl_clear_history();
		free(minis->line);
	}
	if (z == 1)
		free_tab(minis->tab_cmd, minis->nb_cmd + 1);
	if (z >= 2)
		free_struct_cmd(minis);
	if (z >= 3)
		free_redi(minis);
	if (is_perror == 1)
		perror(message);
	else
		ft_putstr_fd(message, 2);
	exit(1);
}

void	ft_error_ptr(t_data *minis, t_var *ptr, int error)
{
	if (error == 1)
	{
		free(ptr);
		ft_error("Malloc", minis, 0, 1);
	}
	if (error == 2)
	{
		free(ptr->name);
		free(ptr);
		ft_error("Malloc", minis, 0, 1);
	}
}

void	ft_error_fork(t_data *minis, int redi_pipe[2][2], int y)
{
	close(redi_pipe[0][1]);
	close(redi_pipe[1][1]);
	close(redi_pipe[0][0]);
	close(redi_pipe[1][0]);
	if (y == 1)
		close_all_pipes(minis);
	ft_error("Fork", minis, 3, 1);
}
