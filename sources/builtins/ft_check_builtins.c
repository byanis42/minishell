/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:07:14 by byanis            #+#    #+#             */
/*   Updated: 2023/04/17 23:07:14 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_digital(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_putstr_fd("numeric argument required\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_free_exit(t_data *minis)
{
	free_struct(minis);
	free_list(minis->env);
}

void	ft_exit(t_data *minis, t_board *cmd)
{
	int	exit_code;
	int	i;

	i = 0;
	ft_putstr_fd("exit\n", 1);
	if (cmd->nb_words > 3)
	{
		ft_putstr_fd("too much argument for exit\n", 2);
		g_code_erreur = 1;
		return ;
	}
	if (cmd->nb_words == 3)
	{
		if (cmd->tab[1][0] == '-')
			i++;
		if (!ft_is_digital(cmd->tab[1] + i))
			exit_code = 255;
		else
			exit_code = ft_atoi(cmd->tab[1]);
	}
	else
		exit_code = 0;
	rl_clear_history();
	ft_free_exit(minis);
	exit(exit_code);
}

void	builtins_with_fork(t_data *minis, t_board *cmd)
{
	if (ft_strcmp(cmd->tab[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->tab[0], "env") == 0)
		ft_envp(minis);
	else if (ft_strcmp(cmd->tab[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->tab[0], "exit") == 0)
		ft_exit(minis, cmd);
	else if (ft_strcmp(cmd->tab[0], "cd") == 0)
		ft_cd(minis, cmd);
	else if (ft_strcmp(cmd->tab[0], "export") == 0)
		ft_export(minis, cmd);
	else if (ft_strcmp(cmd->tab[0], "unset") == 0)
		ft_unset(minis, cmd);
}

void	butiltins_without_fork(t_data *minis, t_board *cmd, int i)
{
	if (minis->nb_cmd != 1 && i != (minis->nb_cmd - 1))
		return ;
	if (ft_strcmp(cmd->tab[0], "exit") == 0)
		ft_exit(minis, cmd);
	else if (ft_strcmp(cmd->tab[0], "cd") == 0)
		ft_cd(minis, cmd);
	else if (ft_strcmp(cmd->tab[0], "export") == 0 && cmd->nb_words > 2)
		ft_export(minis, cmd);
	else if (ft_strcmp(cmd->tab[0], "unset") == 0)
		ft_unset(minis, cmd);
}
