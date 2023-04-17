/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:07:20 by byanis            #+#    #+#             */
/*   Updated: 2023/04/17 23:07:21 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_delete_middle_node(t_var *env)
{
	t_var	*tmp;

	tmp = env->next;
	env->next = tmp->next;
	free(tmp->name);
	free(tmp->value);
	tmp->next = NULL;
	free(tmp);
}

void	ft_delete_last_node(t_var *env)
{
	t_var	*tmp;

	tmp = env->next;
	free(tmp->name);
	free(tmp->value);
	tmp->next = NULL;
	free(tmp);
	env->next = NULL;
}

t_var	*ft_delete_first_node(t_var *env)
{
	t_var	*tmp;

	tmp = env;
	env = env->next;
	if (tmp->name)
		free(tmp->name);
	if (tmp->value)
		free(tmp->value);
	tmp->next = NULL;
	free(tmp);
	return (env);
}

t_var	*ft_delete_node(char *str, t_var *env)
{
	t_var	*tmp;
	t_var	*start;

	start = env;
	if (ft_strcmp(str, env->name) == 0)
	{
		env = ft_delete_first_node(env);
		return (env);
	}
	tmp = env->next;
	while (tmp->next != NULL)
	{
		if (ft_strcmp(str, tmp->name) == 0)
		{
			ft_delete_middle_node(env);
			return (start);
		}
		env = env->next;
		tmp = env->next;
	}
	if (ft_strcmp(str, tmp->name) == 0)
		ft_delete_last_node(env);
	return (start);
}

void	ft_unset(t_data *minis, t_board *cmd)
{
	int	i;

	i = 1;
	while (i < cmd->nb_words - 1)
	{
		minis->env = ft_delete_node(cmd->tab[i], minis->env);
		i++;
	}
}
