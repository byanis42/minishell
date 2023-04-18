/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:08:10 by byanis            #+#    #+#             */
/*   Updated: 2023/04/18 16:13:09 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* La fonction pipe_at_end vérifie si le symbole pipe est situé à la fin
de la chaîne ou immédiatement suivi d'un espace. Si ce n'est pas le cas,
elle renvoie une erreur de syntaxe. */

int	pipe_at_end( char *str, int i)
{
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i] || str[i] == '|')
	{
		ft_putstr_fd("Error parsing : unexpected token `|'\n", 2);
		g_code_erreur = 258;
		return (1);
	}
	return (0);
}

/* La fonction unknow_env_redi vérifie si la chaîne contient une
variable d'environnement non définie, qui se manifeste par
le symbole $ suivi d'une séquence de caractères qui ne correspond
à aucune variable d'environnement connue. */

int	unknow_env_redi(t_data *minis, char *str, int i)
{
	char	*var_env;
	char	*res_env;

	if (str[i] == '$')
	{
		var_env = search_env_var(str, i, minis);
		res_env = list_chr(minis->env, var_env);
		free(var_env);
		if (!res_env || res_env[0] == '\0')
			return (1);
	}
	return (0);
}

/* La fonction check_after_redi vérifie si les caractères
qui suivent une redirection sont valides. Plus précisément,
elle vérifie si un caractère guillemet ou apostrophe correspondant
n'a pas été fermé correctement,
si un symbole pipe (|) suit immédiatement la redirection ou si
la chaîne se termine immédiatement après la redirection. */

int	check_after_redi(char *str, char *new_str, int j, int i)
{
	if (str[j] == 34 || str[j] == 39)
	{
		ft_putstr_fd(" : No such file or directory\n", 2);
		g_code_erreur = 1;
		free(new_str);
		return (1);
	}
	if (new_str[i] == '|')
	{
		ft_putstr_fd("Error parsing : unexpected token `|'\n", 2);
		g_code_erreur = 258;
		free(new_str);
		return (1);
	}
	if (!new_str[i] || ((new_str[i] == '<' || new_str[i] == '>')
			&& is_no_open_quote(str, j)))
	{
		ft_putstr_fd("Error parsing\n", 2);
		g_code_erreur = 258;
		free(new_str);
		return (1);
	}
	return (0);
}

/* La fonction nothing_after_redi vérifie si
une redirection est suivie de quelque chose d'autre que de
caractères d'espacement et de l'indicateur de fin de chaîne.
Elle renvoie une erreur si une variable d'environnement non
définie est présente dans la chaîne.
Elle renvoie également une erreur si la chaîne contient un
caractère guillemet ou apostrophe qui n'a pas été fermé correctement. */

int	nothing_after_redi(t_data *minis, char *str, int i)
{
	char	*new_str;
	int		j;

	new_str = ft_strdup(str);
	if (!new_str)
		ft_error("Malloc", minis, 2, 1);
	new_str = get_new_str(new_str);
	if (!new_str)
		ft_error("Malloc", minis, 2, 1);
	while (new_str[i] && new_str[i] == ' ')
		i++;
	j = i;
	while (str[j] && new_str[i] && new_str[i] != str[j])
		j++;
	if (check_after_redi(str, new_str, j, i))
		return (1);
	if (unknow_env_redi(minis, new_str, i))
	{
		ft_putstr_fd("ambiguous redirect\n", 2);
		g_code_erreur = 1;
		free(new_str);
		return (1);
	}
	free(new_str);
	return (0);
}

/* Enfin, la fonction parse appelle les fonctions ci-dessus pour vérifier
si la chaîne est correctement parsée.
Si c'est le cas, elle renvoie 1, sinon elle renvoie 0. */

int	parse(t_data *minis, char *str)
{
	int	i;

	if (!check_all_spaces(str))
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '|' && is_no_open_quote(str, i))
		{
			if (pipe_at_end(str, i + 1))
				return (0);
		}
		else if ((str[i] == '>' || str[i] == '<' ) && is_no_open_quote(str, i))
		{
			if (str[i + 1] == '>' && str[i] == '>')
				i++;
			else if (str[i + 1] == '<' && str[i] == '<')
				i++;
			if (nothing_after_redi(minis, str, i + 1))
				return (0);
		}
		i++;
	}
	return (1);
}
