/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:36:29 by byanis            #+#    #+#             */
/*   Updated: 2022/11/10 17:07:10 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_c(char comp, char c)
{
	return (c == comp);
}

static int	count_words(const char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && ft_is_c(*str, c))
			str++;
		if (*str && !ft_is_c(*str, c))
		{
			count++;
			while (*str && !ft_is_c(*str, c))
				str++;
		}
	}
	return (count);
}

static char	*malloc_word(const char *str, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i] && !ft_is_c(str[i], c))
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (str[i] && !ft_is_c(str[i], c))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_free_exit(char **arr, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;

	if (!s)
		return (NULL);
	arr = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && ft_is_c(*s, c))
			s++;
		if (*s && !ft_is_c(*s, c))
		{
			arr[i] = malloc_word(s, c);
			if (!arr[i])
				return (ft_free_exit(arr, i));
			i++;
			while (*s && !ft_is_c(*s, c))
				s++;
		}
	}
	arr[i] = NULL;
	return (arr);
}
