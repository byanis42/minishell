/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:09:45 by byanis            #+#    #+#             */
/*   Updated: 2023/04/17 23:09:45 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_env_var(char *str, int j)
{
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_' || str[j] == '?'))
	{
		if (str[j] == '?')
			break ;
		j++;
	}
	return (j);
}

int	ft_len_cmd(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	if (line[i] == '|')
		i++;
	while (line[i])
	{
		if (is_no_open_quote(line, i) && line[i] == '|')
			return (i);
		i++;
	}
	return (i);
}

char	*ft_cpy_new_line_bis(char *cmd, char *var_env, char *new, int i)
{
	int	k;
	int	j;

	k = 0;
	j = 0;
	while (new[j])
		j++;
	while (var_env && var_env[k])
	{
		new[j] = var_env[k];
		j++;
		k++;
	}
	k = i + ft_strlen_var(cmd, i);
	while (cmd[k] && cmd)
	{
		new[j] = cmd[k];
		j++;
		k++;
	}
	new[j] = '\0';
	free(cmd);
	return (new);
}

char	*ft_cpy_new_line(char *cmd, char *var_env, int i, t_data *minis)
{
	int		j;
	char	*new;

	j = ft_strlen(cmd) - ft_strlen_var(cmd, i);
	if (var_env)
		j += ft_strlen(var_env);
	new = malloc(sizeof(char) * (j + 1));
	if (!new)
		ft_error("Malloc", minis, 2, 1);
	j = 0;
	while (j < i && cmd)
	{
		new[j] = cmd[j];
		j++;
	}
	new[j] = '\0';
	new = ft_cpy_new_line_bis(cmd, var_env, new, i);
	return (new);
}

int	is_redi_d_infile(t_redi *ptr)
{
	if (!ptr)
		return (0);
	while (ptr->next != NULL)
	{
		if (ptr->type == D_INFILE)
			return (1);
		ptr = ptr->next;
	}
	if (ptr->type == D_INFILE)
		return (1);
	return (0);
}
