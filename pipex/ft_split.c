/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:37:42 by paperez-          #+#    #+#             */
/*   Updated: 2025/02/10 04:03:09 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	word_cnt(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*next_word(const char *s, char c, int *i)
{
	char	*word;
	int		start;
	int		length;

	start = *i;
	while (s[start] == c)
		start++;
	length = 0;
	while (s[start + length] && s[start + length] != c)
		length++;
	word = ft_substr(s, start, length);
	*i = start + length;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	int		i;
	int		j;
	int		wc;

	i = 0;
	j = 0;
	wc = word_cnt(s, c);
	words = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!words)
		return (NULL);
	while (j < wc)
	{
		words[j] = next_word(s, c, &i);
		j++;
	}
	words[j] = NULL;
	return (words);
}

int	ft_putstr(char *str)
{
	int	c;

	c = 0;
	if (str == 0)
		return (ft_putstr("(null)"));
	while (str[c] != '\0')
	{
		write (1, &str[c], 1);
		c++;
	}
	return (c);
}
