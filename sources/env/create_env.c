/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:07:27 by byanis            #+#    #+#             */
/*   Updated: 2023/04/17 23:07:27 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_get_name(char *str, t_var *ptr)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	ptr->name = malloc(sizeof(char) * (i + 1));
	if (!ptr->name)
	{
		free(ptr);
		return ;
	}
	i = 0;
	while (str[i] && str[i] != '=')
	{
		ptr->name[i] = str[i];
		i++;
	}
	ptr->name[i] = '\0';
}

void	ft_get_value(t_data *minis, char *str, t_var *ptr)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] != '=')
	{
		ft_malloc_empty(minis, ptr);
		return ;
	}
	i++;
	ptr->value = ft_strdup(str + i);
	if (!ptr->value)
	{
		free(ptr->name);
		free(ptr);
		ft_error("Malloc", minis, 3, 1);
	}
}

void	create_var_interr(t_data *minis)
{
	t_var	*ptr;

	ptr = malloc(sizeof(t_var));
	if (!ptr)
		ft_error("Malloc", minis, 0, 1);
	ptr->name = malloc(sizeof(char) * 2);
	if (!ptr->name)
		ft_error_ptr(minis, ptr, 1);
	ptr->name[0] = '?';
	ptr->name[1] = '\0';
	ptr->value = malloc(sizeof(char) * 2);
	if (!ptr->value)
		ft_error_ptr(minis, ptr, 1);
	ptr->value[0] = '1';
	ptr->value[1] = '\0';
	ptr->next = NULL;
	ptr->is_export = 0;
	ptr->is_print = 0;
	lst_add(&minis->env, ptr);
	ptr = NULL;
}

void	create_var(t_data *minis, char **envp, int i)
{
	t_var	*ptr;

	ptr = malloc(sizeof(t_var));
	if (!ptr)
		ft_error("Malloc", minis, 0, 1);
	ft_get_name(envp[i], ptr);
	if (!ptr->name)
		ft_error_ptr(minis, ptr, 1);
	ft_get_value(minis, envp[i], ptr);
	if (!ptr->value)
		ft_error_ptr(minis, ptr, 2);
	if (ptr->name && ptr->name[0] == '_' && ptr->name[1] == '\0')
		ptr->is_export = 0;
	else
		ptr->is_export = 1;
	ptr->is_print = 1;
	ptr->next = NULL;
	lst_add(&minis->env, ptr);
	ptr = NULL;
}

void	ft_create_env(t_data *minis, char **envp)
{
	int	i;

	minis->env = NULL;
	i = 0;
	while (envp[i])
	{
		create_var(minis, envp, i);
		i++;
	}
	create_var_interr(minis);
}
