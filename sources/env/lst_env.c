/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:07:39 by byanis            #+#    #+#             */
/*   Updated: 2023/04/17 23:07:39 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	put_res_pipe(t_data *minis, int res)
{
	t_var	*ptr;
	char	*new_value;

	ptr = lst_name_finding(minis->env, "?");
	new_value = ft_itoa(res);
	if (!new_value)
		ft_error("Malloc", minis, 3, 1);
	free(ptr->value);
	ptr->value = ft_strdup(new_value);
	if (!ptr->value)
	{
		free(new_value);
		ft_error("Malloc", minis, 3, 1);
	}
	free(new_value);
}

t_var	*lst_name_finding(t_var *lst, char *name)
{
	while (lst->next != NULL && ft_strcmp(lst->name, name) != 0)
		lst = lst->next;
	if (ft_strcmp(lst->name, name) == 0)
		return (lst);
	else
		return (NULL);
}

t_var	*lst_last(t_var *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	lst_add(t_var **lst, t_var *new)
{
	t_var	*aux_lst;

	if (new)
	{
		if (!*lst)
		{
			*lst = new;
			return ;
		}
		aux_lst = lst_last(*lst);
		aux_lst->next = new;
	}
}

void	ft_malloc_empty(t_data *minis, t_var *ptr)
{
	ptr->value = malloc(sizeof(char) * 1);
	if (!ptr->value)
		ft_error("Malloc", minis, 3, 1);
	ptr->value[0] = '\0';
}
