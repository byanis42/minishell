/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:08:35 by byanis            #+#    #+#             */
/*   Updated: 2023/04/18 16:14:26 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Cette fonction copie le nom de la commande stockée dans le tableau tab
d'une structure t_board dans une chaîne de caractères. */

void	cpy_cmd(t_board *cmd, char *poss, int i)
{
	int	j;

	j = 0;
	while (cmd->tab[0][j])
	{
		poss[i] = cmd->tab[0][j];
		i++;
		j++;
	}
	poss[i] = '\0';
}

/* Cette fonction copie une partie d'un chemin d'accès depuis une variable
d'environnement PATH dans une nouvelle chaîne de caractères.
La fonction prend également une structure t_board et retourne la chaîne
nouvellement créée. */

char	*cpy_path(t_data *minis, t_board *cmd, char *path, int *path_len)
{
	int		i;
	char	*poss;

	*path_len = 0;
	while (path[*path_len] && path[*path_len] != ':')
		(*path_len)++;
	i = *path_len;
	i += ft_strlen(cmd->tab[0]);
	poss = malloc(sizeof(char) * (i + 2));
	if (!poss)
		ft_error("Malloc", minis, 3, 1);
	i = 0;
	while (path[i] && path[i] != ':')
	{
		poss[i] = path[i];
		i++;
	}
	poss[i] = '/';
	i++;
	cpy_cmd(cmd, poss, i);
	return (poss);
}

/* Cette fonction vérifie si l'exécution du programme est autorisée
ou non en utilisant la fonction access et retourne le nom de la commande si
elle peut être exécutée et NULL sinon. Si l'accès est refusé,
la fonction affiche un message d'erreur et affecte la variable globale
g_code_erreur à 126. */

char	*check_acces_path(t_data *minis, t_board *cmd)
{
	char	*res;

	if (!cmd->tab[0])
		return (NULL);
	if (access(cmd->tab[0], F_OK) == 0 && access(cmd->tab[0], X_OK) != 0)
	{
		res = ft_strdup(cmd->tab[0]);
		if (!res)
			ft_error("Malloc", minis, 3, 1);
		ft_putstr_fd("Permission denied :", 2);
		ft_putstr_fd(cmd->tab[0], 2);
		ft_putchar_fd('\n', 2);
		g_code_erreur = 126;
		return (res);
	}
	if (access(cmd->tab[0], X_OK) == 0 && !access_check(cmd->tab[0]))
	{
		res = ft_strdup(cmd->tab[0]);
		if (!res)
			ft_error("Malloc", minis, 3, 1);
		return (res);
	}
	return (NULL);
}

/* Cette fonction est utilisée pour déterminer si nous devons avancer
le pointeur vers le prochain chemin dans la variable d'environnement PATH. */

int	ft_move_path(char *path, int *path_len)
{
	if (path[*path_len] == ':')
		return (1);
	return (0);
}

/* Cette fonction prend une structure t_data, une chaîne de caractères path,
et une structure t_board.
La fonction essaie de trouver le chemin complet de la commande cmd dans la
variable d'environnement PATH en appelant les fonctions précédemment décrites.
La fonction retourne NULL si la commande n'a pas été trouvée ou le chemin
complet de la commande si elle a été trouvée. */

char	*ft_try_path(t_data *minis, char *path, t_board *cmd)
{
	char	*poss;
	char	*res;
	int		path_len;

	res = check_acces_path(minis, cmd);
	if (res)
		return (res);
	if (!path || !*path)
		return (NULL);
	poss = cpy_path(minis, cmd, path, &path_len);
	if (access(poss, X_OK) == 0)
		return (poss);
	path += ft_move_path(path, &path_len);
	if (path[path_len])
	{
		res = ft_try_path(minis, path + path_len, cmd);
		if (res)
		{
			free(poss);
			return (res);
		}
	}
	free(poss);
	return (NULL);
}
