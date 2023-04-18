/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:07:20 by byanis            #+#    #+#             */
/*   Updated: 2023/04/18 14:05:24 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* La fonction ft_delete_middle_node prend en entrée un pointeur vers
une variable d'environnement env et
supprime le nœud suivant à celui pointé par env. */

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

/* La fonction ft_delete_last_node prend en entrée un pointeur vers une variable
d'environnement env et supprime le dernier nœud. */

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

/* La fonction ft_delete_first_node prend en entrée un pointeur vers
une variable d'environnement env et supprime le premier nœud. */

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

/* La fonction ft_delete_node prend en entrée une chaîne de caractères str
et un pointeur vers une variable d'environnement env et supprime
le nœud correspondant à la chaîne str. */

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

/* La fonction ft_unset prend en entrée un pointeur vers une structure minis
et un pointeur vers une structure cmd qui contient les arguments
de la commande unset.
Cette fonction appelle la fonction ft_delete_node pour chaque argument
de la commande unset, et supprime les nœuds correspondants de la liste
chaînée env de minis. */

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
