/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:07:49 by byanis            #+#    #+#             */
/*   Updated: 2023/04/17 23:07:49 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_code_erreur;

int	check_all_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

void	each_things_to_do(t_data *minis, char **envp)
{
	int	res;

	add_history(minis->line);
	put_res_pipe(minis, g_code_erreur);
	if (!parse(minis, minis->line))
		return ;
	line_to_cmd(minis);
	init_struct(minis);
	put_env_var(minis);
	redirection(minis);
	ft_split_cmd(minis);
	delete_quote(minis);
	res = ft_pipe(minis, envp);
	if (!ft_is_not_fork(&minis->cmd[minis->nb_cmd - 1]) && g_code_erreur != 126)
		g_code_erreur = res;
	if (minis->cmd[minis->nb_cmd - 1].var_env_empty)
		g_code_erreur = 0;
	check_directory(minis);
	free_struct((minis));
}

void	minishell_loop(char **envp)
{
	t_data	minis;

	g_code_erreur = 0;
	ft_create_env(&minis, envp);
	while (1)
	{
		init_signals();
		minis.line = readline("minishell$ ");
		if (!minis.line)
		{
			line_empty(&minis);
		}
		else if (minis.line && *minis.line)
			each_things_to_do(&minis, envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 1)
		minishell_loop(envp);
	(void)argv;
	(void)argc;
	return (1);
}
