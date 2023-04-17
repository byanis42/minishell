/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:07:34 by byanis            #+#    #+#             */
/*   Updated: 2023/04/17 23:07:34 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strlen_var(char *str, int j)
{
	int	i;

	i = 1;
	j++;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_' || str[j] == '?'))
	{
		i++;
		if (str[j] == '?')
			break ;
		j++;
	}
	return (i);
}

char	*search_env_var(char *str, int i, t_data *minis)
{
	char	*new;
	int		k;
	int		j;

	j = i + 1;
	j = len_env_var(str, j);
	new = malloc(sizeof(char) * (j + 1));
	if (!new)
		ft_error("Malloc", minis, 2, 1);
	j = i + 1;
	k = 0;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_' || str[j] == '?'))
	{
		new[k] = str[j];
		k++;
		if (str[j] == '?')
			break ;
		j++;
	}
	new[k] = '\0';
	return (new);
}

int	is_an_other_var_env(char *var_env)
{
	int	j;

	j = 0;
	while (var_env[j] && var_env[j] != '$')
		j++;
	if ((size_t)j != ft_strlen(var_env))
		return (1);
	return (0);
}

char	*get_envp_var(t_data *minis, char *cmd, int *empty)
{
	char	*var_env;
	char	*res_env;
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$' && is_no_open_single_quote(cmd, i) && cmd[i + 1]
			&& (ft_isalnum(cmd[i + 1])
				|| cmd[i + 1] == '_' || cmd[i + 1] == '?'))
		{
			var_env = search_env_var(cmd, i, minis);
			res_env = list_chr(minis->env, var_env);
			if (res_env == NULL || is_empty(res_env) == 0)
				*empty = 1;
			free(var_env);
			var_env = ft_cpy_new_line(cmd, res_env, i, minis);
			if (is_an_other_var_env(var_env))
				var_env = get_envp_var(minis, var_env, empty);
			return (var_env);
		}
		i++;
	}
	return (cmd);
}

void	put_env_var(t_data *ms)
{
	int	i;
	int	empty;

	i = 0;
	while (i < ms->nb_cmd)
	{
		empty = 0;
		ms->cmd[i].line_cmd = get_envp_var(ms, ms->cmd[i].line_cmd, &empty);
		if (is_empty(ms->cmd[i].line_cmd) == 0 && empty == 1)
			ms->cmd[i].var_env_empty = 1;
		else
			ms->cmd[i].var_env_empty = 0;
		i++;
	}
}
