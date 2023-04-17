/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:06:51 by byanis            #+#    #+#             */
/*   Updated: 2023/04/17 23:06:51 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_name(char *str, t_data *minis)
{
	int		i;
	char	*str_ret;

	str_ret = NULL;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	str_ret = malloc(sizeof(char) * (i + 1));
	if (!str_ret)
		ft_error("Malloc", minis, 2, 1);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		str_ret[i] = str[i];
		i++;
	}
	str_ret[i] = '\0';
	return (str_ret);
}

void	ft_assign_new_value(t_data *minis, char *str, char *name)
{
	t_var	*ptr;

	ptr = lst_name_finding(minis->env, name);
	free(ptr->value);
	ft_get_value(minis, str, ptr);
}

void	ft_create_variable(t_data *minis, char *str)
{
	t_var	*ptr;

	ptr = malloc(sizeof(t_var));
	if (!ptr)
		ft_error("Malloc", minis, 3, 1);
	ptr->next = NULL;
	ft_get_value(minis, str, ptr);
	if (!ptr->value)
		ft_error("Malloc", minis, 3, 1);
	ft_get_name(str, ptr);
	if (!ptr->name)
		ft_error("Malloc", minis, 3, 1);
	ptr->is_export = 1;
	ptr->is_print = 1;
	lst_add(&minis->env, ptr);
	ptr = NULL;
}

int	export_arg(t_data *minis, t_board *cmd, int i)
{
	char	*name;

	name = get_name(cmd->tab[i], minis);
	if (ft_strchr(cmd->tab[i], '=') && !list_chr(minis->env, name))
		ft_create_variable(minis, cmd->tab[i]);
	else if (ft_strchr(cmd->tab[i], '=') && list_chr(minis->env, name))
		ft_assign_new_value(minis, cmd->tab[i], name);
	else if (!ft_strchr(cmd->tab[i], '=') && list_chr(minis->env, name))
	{
		free(name);
		return (0);
	}
	else if (!ft_strchr(cmd->tab[i], '=') && !list_chr(minis->env, name))
		ft_create_variable(minis, cmd->tab[i]);
	free(name);
	return (1);
}

void	ft_export(t_data *minis, t_board *cmd)
{
	int	i;

	if (cmd->nb_words == 2)
	{
		print_list(minis->env, 1);
		g_code_erreur = 0;
		return ;
	}
	i = 1;
	while (i < cmd->nb_words - 1)
	{
		if (!export_arg(minis, cmd, i))
			return ;
		i++;
	}
	g_code_erreur = 0;
}
