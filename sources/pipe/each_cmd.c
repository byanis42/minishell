/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   each_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:08:24 by byanis            #+#    #+#             */
/*   Updated: 2023/04/17 23:08:24 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_empty(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			count++;
		i++;
	}
	return (count);
}

int	just_one_cmd(t_data *minis, t_board *cmd, char **envp)
{
	int	redi_pipe[2][2];
	int	res;

	if (!infile_error_message(&minis->cmd[0], 1))
		return (1);
	if (ft_is_not_fork(cmd))
	{
		butiltins_without_fork(minis, cmd, 0);
		return (0);
	}
	ft_pipe_redi(minis, redi_pipe);
	init_signals_child();
	cmd->res_fork = fork();
	if (cmd->res_fork < 0)
		ft_error_fork(minis, redi_pipe, 0);
	if (cmd->res_fork == 0)
		fork_one_cmd(minis, envp, redi_pipe, cmd);
	close_redi_pipe(redi_pipe);
	waitpid(minis->cmd[0].res_fork, &res, 0);
	return (res);
}

void	first_cmd(t_data *minis, char **envp, int i)
{
	t_board	*cmd;
	int		redi_pipe[2][2];

	cmd = &minis->cmd[i];
	if (error_or_not_fork(minis, cmd, 1, i))
		return ;
	ft_pipe_redi(minis, redi_pipe);
	cmd->res_fork = fork();
	if (cmd->res_fork < 0)
		ft_error_fork(minis, redi_pipe, 1);
	if (cmd->res_fork == 0)
		fork_first_cmd(minis, envp, redi_pipe, i);
	close_redi_pipe(redi_pipe);
}

void	middle_cmd(t_data *minis, char **envp, int i)
{
	t_board	*cmd;
	int		redi_pipe[2][2];

	cmd = &minis->cmd[i];
	if (error_or_not_fork(minis, cmd, 2, i))
		return ;
	ft_pipe_redi(minis, redi_pipe);
	cmd->res_fork = fork();
	if (cmd->res_fork < 0)
		ft_error_fork(minis, redi_pipe, 1);
	if (cmd->res_fork == 0)
		fork_middle_cmd(minis, envp, redi_pipe, i);
	close_redi_pipe(redi_pipe);
}

void	last_cmd(t_data *minis, char **envp, int i)
{
	t_board	*cmd;
	int		redi_pipe[2][2];

	cmd = &minis->cmd[i];
	if (error_or_not_fork(minis, cmd, 3, i))
		return ;
	ft_pipe_redi(minis, redi_pipe);
	cmd->res_fork = fork();
	if (cmd->res_fork < 0)
		ft_error_fork(minis, redi_pipe, 1);
	if (cmd->res_fork == 0)
		fork_last_cmd(minis, envp, redi_pipe, i);
	close_redi_pipe(redi_pipe);
}
