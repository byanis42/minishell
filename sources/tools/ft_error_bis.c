/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:09:18 by byanis            #+#    #+#             */
/*   Updated: 2023/04/17 23:09:18 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error_to_pipe(t_data *minis, int i)
{
	int	z;

	z = 0;
	while (z < i)
	{
		close(minis->cmd[z].pipe_fd[0]);
		close(minis->cmd[z].pipe_fd[1]);
			z++;
	}
	ft_error("Pipe", minis, 3, 1);
}
