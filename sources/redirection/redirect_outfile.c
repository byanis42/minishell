/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_outfile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:08:59 by byanis            #+#    #+#             */
/*   Updated: 2023/04/17 23:08:59 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirect_error(t_data *minis, int redi_pipe[2][2])
{
	close(redi_pipe[0][0]);
	close(redi_pipe[1][0]);
	if (minis->nb_cmd > 1)
		close_all_pipes(minis);
	ft_error("Malloc", minis, 3, 1);
}

int	redirect_outfile(t_board *cmd, int redi_pipe[2])
{
	t_redi	*ptr;

	ptr = cmd->redi;
	if (!ptr)
		return (0);
	open_all_redi_files(cmd);
	ptr = last_redi_out(cmd->redi);
	if (!ptr)
		return (0);
	dup2(ptr->file_fd, redi_pipe[1]);
	close_all_redi_files(cmd);
	return (1);
}
