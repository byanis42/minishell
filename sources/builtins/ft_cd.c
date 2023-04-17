/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:49:09 by byanis            #+#    #+#             */
/*   Updated: 2023/04/17 23:06:59 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	access_check(char *path)
{
	DIR	*c;

	c = opendir(path);
	if (c == NULL)
		return (ERROR);
	closedir(c);
	return (SUCCESS);
}

void	ft_change_oldpwd(t_var *env, t_data *minis)
{
	char	*path;
	t_var	*ptr;

	path = list_chr(env, "PWD");
	if (!path)
		ft_error("Cd failed\n", minis, 2, 0);
	ptr = lst_name_finding(env, "OLDPWD");
	free(ptr->value);
	ptr->value = ft_strdup(path);
	ptr = NULL;
}

void	ft_change_pwd(t_var *env, t_data *minis)
{
	char	path[PATH_LEN];
	t_var	*ptr;

	getcwd(path, PATH_LEN);
	if (!*path)
		ft_error("Getcwd", minis, 2, 1);
	ptr = lst_name_finding(env, "PWD");
	free(ptr->value);
	ptr->value = ft_strdup(path);
	ptr = NULL;
}

int	cd_without_arg(t_data *minis, t_board *cmd)
{
	t_var	*ptr;

	if (cmd->nb_words > 2)
		return (0);
	ptr = lst_name_finding(minis->env, "HOME");
	if (access_check(ptr->value) == ERROR)
	{
		ft_putstr_fd("wrong path or not authorized\n", 2);
		g_code_erreur = 1;
		return (1);
	}
	if (chdir(ptr->value) == -1)
	{
		ft_putstr_fd("ERROR CHANGING DIR\n", 2);
		g_code_erreur = 1;
		return (1);
	}
	ft_change_oldpwd(minis->env, minis);
	ft_change_pwd(minis->env, minis);
	g_code_erreur = 0;
	return (1);
}

void	ft_cd(t_data *minis, t_board *cmd)
{
	char	*home_dir;

	if (cd_without_arg(minis, cmd))
		return ;
	home_dir = cmd->tab[1];
	if (access_check(home_dir) == ERROR)
	{
		ft_putstr_fd("wrong path or not authorized\n", 2);
		g_code_erreur = 1;
		return ;
	}
	if (chdir(home_dir) == -1)
	{
		ft_putstr_fd("ERROR CHANGING DIR\n", 2);
		g_code_erreur = 1;
		return ;
	}
	ft_change_oldpwd(minis->env, minis);
	ft_change_pwd(minis->env, minis);
	g_code_erreur = 0;
}
