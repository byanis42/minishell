/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:49:09 by byanis            #+#    #+#             */
/*   Updated: 2023/04/18 15:22:52 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Cette fonction prend en paramètre un chemin de fichier ou de dossier
et vérifie s'il est accessible.
Elle utilise la fonction opendir pour vérifier si le dossier existe et si
l'utilisateur a le droit d'y accéder. Si opendir retourne NULL, cela signifie
que l'accès est interdit ou que le dossier n'existe pas, et la fonction renvoie
une erreur (constante 'ERROR' définie dans le header).
Sinon, elle renvoie 'SUCCESS'. */

int	access_check(char *path)
{
	DIR	*c;

	c = opendir(path);
	if (c == NULL)
		return (ERROR);
	closedir(c);
	return (SUCCESS);
}

/* Cette fonction prend en paramètre un pointeur vers la liste chaînée
des variables d'environnement, ainsi qu'un pointeur vers la structure
contenant les données du shell. Elle modifie la valeur de la variable
d'environnement "OLDPWD" en y mettant la valeur de la variable
d'environnement "PWD". Cette fonction est utilisée pour mettre à jour la
variable "OLDPWD" après que l'utilisateur ait changé de répertoire
avec la commande 'cd'. */

void	ft_change_oldpwd(t_var *env, t_data *minis)
{
	char	*path;
	t_var	*ptr;

	path = list_chr(env, "PWD");
	if (!path)
		ft_error("Cd failed\n", minis, 2, 0);
	ptr = lst_name_finding(env, "OLDPWD");
	free(ptr->value);
	ptr->value = ft_strdup(path);
	ptr = NULL;
}

/* Cette fonction prend en paramètre un pointeur vers la liste chaînée
des variables d'environnement, ainsi qu'un pointeur vers la structure
contenant les données du shell. Elle modifie la valeur de la variable
d'environnement "PWD" en y mettant le chemin du répertoire courant
obtenu en utilisant la fonction getcwd.
Cette fonction est utilisée pour mettre à jour la variable "PWD" après
que l'utilisateur ait changé de répertoire avec la commande 'cd'. */

void	ft_change_pwd(t_var *env, t_data *minis)
{
	char	path[PATH_LEN];
	t_var	*ptr;

	getcwd(path, PATH_LEN);
	if (!*path)
		ft_error("Getcwd", minis, 2, 1);
	ptr = lst_name_finding(env, "PWD");
	free(ptr->value);
	ptr->value = ft_strdup(path);
	ptr = NULL;
}

/* Cette fonction prend en paramètre un pointeur vers la structure
contenant les données du shell, ainsi qu'un pointeur vers la structure
t_board contenant les arguments de la commande 'cd'.
Elle vérifie si la commande 'cd' a été appelée sans argument.
Si tel est le cas, elle récupère le chemin du répertoire utilisateur
en accédant à la variable d'environnement "HOME".
Elle vérifie ensuite si l'utilisateur a le droit d'accéder à ce
répertoire en appelant la fonction access_check. Si l'accès est autorisé,
elle change de répertoire en utilisant la fonction chdir.
Elle appelle également les fonctions ft_change_oldpwd et ft_change_pwd
pour mettre à jour les variables "OLDPWD" et "PWD".
Enfin, elle renvoie 1 pour indiquer que la commande a été exécutée. */

int	cd_without_arg(t_data *minis, t_board *cmd)
{
	t_var	*ptr;

	if (cmd->nb_words > 2)
		return (0);
	ptr = lst_name_finding(minis->env, "HOME");
	if (access_check(ptr->value) == ERROR)
	{
		ft_putstr_fd("wrong path or not authorized\n", 2);
		g_code_erreur = 1;
		return (1);
	}
	if (chdir(ptr->value) == -1)
	{
		ft_putstr_fd("ERROR CHANGING DIR\n", 2);
		g_code_erreur = 1;
		return (1);
	}
	ft_change_oldpwd(minis->env, minis);
	ft_change_pwd(minis->env, minis);
	g_code_erreur = 0;
	return (1);
}

/* Cette fonction prend en paramètre un pointeur vers la structure
contenant les données du shell, ainsi qu'un pointeur vers
la structure t_board contenant les arguments de la commande 'cd'.
Cette fonction vérifie si la commande 'cd' a été appelée
avec un argument.
Si tel est le cas, elle utilise l'argument comme chemin
de répertoire à changer.
Elle vérifie ensuite si l'utilisateur a le droit d'accéder
à ce répertoire en appelant la fonction access_check.
Si l'accès est autorisé, elle change de répertoire en utilisant
la fonction chdir. Elle appelle également les fonctions
ft_change_oldpwd et ft_change_pwd pour mettre à jour les variables
"OLDPWD" et "PWD".
Enfin, elle renvoie 1 pour indiquer que la commande a été exécutée. */

void	ft_cd(t_data *minis, t_board *cmd)
{
	char	*home_dir;

	if (cd_without_arg(minis, cmd))
		return ;
	home_dir = cmd->tab[1];
	if (access_check(home_dir) == ERROR)
	{
		ft_putstr_fd("wrong path or not authorized\n", 2);
		g_code_erreur = 1;
		return ;
	}
	if (chdir(home_dir) == -1)
	{
		ft_putstr_fd("ERROR CHANGING DIR\n", 2);
		g_code_erreur = 1;
		return ;
	}
	ft_change_oldpwd(minis->env, minis);
	ft_change_pwd(minis->env, minis);
	g_code_erreur = 0;
}
