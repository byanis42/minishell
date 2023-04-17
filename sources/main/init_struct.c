/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:07:45 by byanis            #+#    #+#             */
/*   Updated: 2023/04/17 23:07:45 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_first_node_redi(t_board *cmd)
{
	t_redi	*ptr;

	ptr = cmd->redi;
	if (!ptr)
		return ;
	if (ptr->next)
		cmd->redi = ptr->next;
	else
		cmd->redi = NULL;
	if (ptr->file)
		free(ptr->file);
	ptr->file = NULL;
	ptr->next = NULL;
	free(ptr);
	ptr = NULL;
}

void	free_redi(t_data *minis)
{
	int	i;

	i = 0;
	while (i < minis->nb_cmd)
	{
		if (minis->cmd[i].redi != NULL)
		{
			while (minis->cmd[i].redi)
				delete_first_node_redi(&minis->cmd[i]);
		}
		i++;
	}
}

void	free_struct(t_data *minis)
{
	free_redi(minis);
	free_struct_cmd(minis);
	free(minis->line);
}

void	init_struct(t_data *minis)
{
	int	i;

	minis->cmd = malloc(sizeof(t_board) * minis->nb_cmd);
	if (!minis->cmd)
		ft_error("Malloc", minis, 1, 1);
	i = 0;
	while (i < minis->nb_cmd)
	{
		minis->cmd[i].line_cmd = ft_strdup(minis->tab_cmd[i]);
		if (!minis->cmd[i].line_cmd)
			ft_error("Malloc", minis, 2, 1);
		minis->cmd[i].cmd_path = NULL;
		i++;
	}
	free_tab(minis->tab_cmd, minis->nb_cmd + 1);
}
