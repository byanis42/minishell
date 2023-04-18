/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:06:51 by byanis            #+#    #+#             */
/*   Updated: 2023/04/18 14:24:58 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Cette fonction prend en entrée une chaîne de caractères contenant une
variable d'environnement déclarée sous la forme "nom=valeur" et renvoie
une nouvelle chaîne de caractères contenant uniquement le nom de la variable.
La fonction alloue dynamiquement la mémoire nécessaire pour la nouvelle
chaîne de caractères. */

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

/* Cette fonction prend en entrée une chaîne de caractères contenant
une variable d'environnement déclarée sous la forme "nom=valeur" et le nom
de la variable. La fonction met à jour la valeur de la variable d'environnement
correspondante dans la liste chaînée des variables d'environnement de minis
en remplaçant l'ancienne valeur par la nouvelle valeur de
la variable passée en argument. */

void	ft_assign_new_value(t_data *minis, char *str, char *name)
{
	t_var	*ptr;

	ptr = lst_name_finding(minis->env, name);
	free(ptr->value);
	ft_get_value(minis, str, ptr);
}

/* Cette fonction prend en entrée une chaîne de caractères contenant
une variable d'environnement déclarée sous la forme "nom=valeur".
La fonction crée une nouvelle variable d'environnement dans la liste chaînée
des variables d'environnement de minis et y insère le nom et la valeur
de la variable passée en argument. */

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

/* Cette fonction prend en entrée minis, qui est un pointeur vers
une structure t_data, cmd, qui est un pointeur vers une structure
t_board, et i, qui est un entier. La fonction examine l'argument
cmd->tab[i] de la commande "export" pour déterminer s'il s'agit
d'une nouvelle variable d'environnement à créer ou d'une variable
d'environnement existante à mettre à jour. La fonction crée ou
met à jour la variable d'environnement appropriée et retourne 1 si
elle réussit, ou 0 sinon. */

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

/* Cette fonction prend en entrée minis, qui est un pointeur vers
une structure t_data, et cmd, qui est un pointeur vers une
structure t_board. La fonction exécute la commande "export" dans
le shell en créant ou mettant à jour les variables d'environnement
correspondantes pour chaque argument passé en argument de la commande.
Si aucun argument n'est passé, la fonction affiche toutes les variables
d'environnement existantes. */

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
