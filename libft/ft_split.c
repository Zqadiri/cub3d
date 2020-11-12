/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 22:52:00 by zqadiri           #+#    #+#             */
/*   Updated: 2020/10/23 22:49:28 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*static int			words_counter(char const *s, char c)
{
	int		i;
	int		w;

	i = 0;
	w = 0;
	while (s[i])
	{
		if (s[i] == c && s[i])
			i++;
		else if (s[i] != c && s[i])
		{
			w++;
			i++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (w);
}

static size_t		word_length(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

static void			clean(char **split, int c)
{
	while (c >= 0)
	{
		free(split[c]);
		c--;
	}
	free(split);
}

static char			*next_word(const char *s, char c)
{
	int	i;

	i = 0;
	while (*s && *s == c)
		s++;
	return ((char *)s);
}

char				**ft_split(char const *s, char c)
{
	size_t		i;
	size_t		words;
	char		**split;

	i = 0;
	if (!s)
		return (NULL);
	words = words_counter((char *)s, c);
	split = (char **)malloc((words + 1) * sizeof(char*));
	if (split == NULL)
		return (NULL);
	while (i < words)
	{
		s = next_word(s, c);
		split[i] = ft_substr(s, 0, word_length(s, c));
		if (split[i] == NULL)
		{
			clean(split, i);
			return (NULL);
		}
		i++;
		s += word_length(s, c);
	}
	split[words] = NULL;
	return (split);
}*/

char			**ft_free(char **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static int	ft_nbwords(const char *s, char c)
{
	int		nb;
	int		i;

	nb = 0;
	i = 0;
	while (*s != '\0')
	{
		if (i == 1 && *s == c)
			i = 0;
		if (i == 0 && *s != c)
		{
			i = 1;
			nb++;
		}
		s++;
	}
	return (nb);
}

static int	ft_wordlen(const char *s, char c, int i)
{
	int		len;

	len = 0;
	while (s[i + len] != c && s[i + len] != '\0')
		len++;
	return (len);
}

char		**ft_split(const char *s, char c)
{
	char	**tab;
	int		i;
	int		k;
	int		len;
	int		nb_words;

	if (!s || !c)
		return (NULL);
	i = -1;
	k = 0;
	nb_words = ft_nbwords((const char *)s, c);
	if (!(tab = (char **)malloc(sizeof(*tab) * (nb_words + 1))))
		return (NULL);
	while (s[++i] != '\0')
	{
		if (s[i] != c)
		{
			len = ft_wordlen(s, c, i);
			if (!(tab[k++] = ft_substr(s, i, len)))
				return (ft_free(tab, k));
			i = i + len - 1;
		}
	}
	tab[k] = NULL;
	return (tab);
}
