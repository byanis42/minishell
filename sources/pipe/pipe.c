/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:08:44 by byanis            #+#    #+#             */
/*   Updated: 2023/04/17 23:08:44 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_all_pipes(t_data *minis)
{
	int	i;

	i = 0;
	while (i < minis->nb_cmd - 1)
	{
		close(minis->cmd[i].pipe_fd[0]);
		close(minis->cmd[i].pipe_fd[1]);
		i++;
	}
}

void	find_path_struct(t_data *minis)
{
	char	*path;
	int		i;

	i = 0;
	path = list_chr(minis->env, "PATH");
	while (i < minis->nb_cmd)
	{
		if (!ft_is_builtins(&minis->cmd[i]))
		{
			if (!minis->cmd[i].tab[0] || minis->cmd[i].tab[0][0] == '\0')
			{
				i++;
				continue ;
			}
			minis->cmd[i].cmd_path = ft_try_path(minis, path, &minis->cmd[i]);
		}
		i++;
	}
	return ;
}

void	create_pipe(t_data *minis)
{
	int	i;

	i = 0;
	while (i < minis->nb_cmd - 1)
	{
		if (pipe(minis->cmd[i].pipe_fd) == -1)
			ft_error_to_pipe(minis, i);
		i++;
	}
}

int	ft_pipe(t_data *minis, char **envp)
{
	int	res;

	find_path_struct(minis);
	if (minis->nb_cmd == 1)
		res = just_one_cmd(minis, &minis->cmd[0], envp);
	else
	{
		create_pipe(minis);
		res = ft_execute(minis, envp);
	}
	if (res >= 2 && res <= 31)
		return (res + 128);
	if (res % 256 == 0)
		res /= 256;
	if (!ft_is_not_fork(&minis->cmd[minis->nb_cmd - 1])
		&& ft_is_builtins(&minis->cmd[minis->nb_cmd - 1]))
		res = 0;
	if (!minis->cmd[minis->nb_cmd - 1].cmd_path
		&& !ft_is_builtins(&minis->cmd[minis->nb_cmd - 1]))
		return (127);
	return (res);
}
