/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:09:09 by byanis            #+#    #+#             */
/*   Updated: 2023/04/17 23:09:09 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*cpy_redi(char *new_str, int i)
{
	char	*new;
	int		j;

	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (new_str[i] && new_str[i] == ' ')
		i++;
	j = 0;
	while (new_str[i] && new_str[i] != ' '
		&& new_str[i] != '<' && new_str[i] != '>')
	{
		new[j] = new_str[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (new);
}

char	*get_file_redi(t_data *minis, char *str)
{
	char	*new_str;
	char	*new;
	int		i;
	int		len;

	len = 0;
	new_str = ft_strdup(str);
	if (!new_str)
		ft_error("Malloc", minis, 3, 1);
	new_str = get_new_str(new_str);
	if (!new_str)
		ft_error("Malloc", minis, 3, 1);
	i = 0;
	while (new_str[i] && new_str[i] == ' ')
		i++;
	while (new_str[i] && new_str[i] != ' '
		&& new_str[i] != '>' && new_str[i] != '<')
	{
		len++;
		i++;
	}
	new = cpy_redi(new_str, len);
	free(new_str);
	return (new);
}

void	stock_redi(t_data *minis, t_board *cmd, char *str, int res)
{
	t_redi	*redi;
	int		j;

	j = 0;
	if (res == INFILE || res == OUTFILE)
		j = 1;
	else if (res == D_INFILE || res == D_OUTFILE)
		j = 2;
	redi = malloc(sizeof(t_redi));
	if (!redi)
		ft_error("Malloc", minis, 3, 1);
	redi->type = res;
	redi->file = get_file_redi(minis, str + j);
	if (!redi->file)
	{
		free(redi);
		ft_error("Malloc", minis, 3, 1);
	}
	redi->next = NULL;
	lst_add_redi(&cmd->redi, redi);
}

void	clean_this_redi(char *str, int j, int res)
{
	str[j] = ' ';
	if (res == D_INFILE || res == D_OUTFILE)
	{
		j++;
		str[j] = ' ';
	}
	while (str[j] && str[j] == ' ')
		j++;
	while (str[j] && str[j] != ' ' && str[j] != '>' && str[j] != '<')
	{
		str[j] = ' ';
		j++;
	}
}

void	redirection(t_data *minis)
{
	int		i;
	size_t	j;
	int		res;

	i = 0;
	while (i < minis->nb_cmd)
	{
		j = 0;
		minis->cmd[i].redi = NULL;
		while (j < ft_strlen(minis->cmd[i].line_cmd))
		{
			res = ft_is_redi(minis->cmd[i].line_cmd, j);
			if (res != 0)
			{
				stock_redi(minis, &minis->cmd[i],
					minis->cmd[i].line_cmd + j, res);
				clean_this_redi(minis->cmd[i].line_cmd, j, res);
				if (res == D_INFILE || res == D_OUTFILE)
					j++;
			}
			j++;
		}
		i++;
	}
}
