/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:42:35 by threiss           #+#    #+#             */
/*   Updated: 2021/09/18 17:42:37 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	ft_is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_get_words_tab(char const *str)
{
	int	words;
	int	i;

	if (ft_is_space(str[0]))
		words = 0;
	else
		words = 1;
	i = 1;
	while (str[i])
	{
		while (str[i] && ft_is_space(str[i]) == 1)
			i++;
		if (str[i] && !ft_is_space(str[i]) && ft_is_space(str[i - 1]) == 1)
		{
			words++;
			i++;
		}
		while (str[i] && !ft_is_space(str[i]))
			i++;
	}
	return (words);
}

int	ft_get_words(char const *str, char c)
{
	int	words;
	int	i;

	if (c == ' ')
		return (ft_get_words_tab(str));
	if (str[0] == c)
		words = 0;
	else
		words = 1;
	i = 1;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != c && str[i] && str[i - 1] == c)
		{
			words++;
			i++;
		}
		while (str[i] && str[i] != c)
			i++;
	}
	return (words);
}

/*
 **	c = 32
 */

char	**ft_split(char const *str, char c)
{
	int		i;
	int		i_res;
	char	**res;
	int		len;

	i = 0;
	i_res = -1;
	res = malloc((ft_get_words(str, c) + 1) * sizeof(char *));
	if (!str || !res)
		return (0);
	while (str[i] && ft_get_words(str, c) > 0)
	{
		len = 0;
		while (str[i] == c || (str[i] >= 9 && str[i] <= 13))
			i++;
		while (str[i] && str[i] != c && !(str[i] >= 9 && str[i] <= 13))
		{
			len++;
			i++;
		}
		if (len > 0)
			res[++i_res] = ft_substr(str, i - len, len);
	}
	res[++i_res] = 0;
	return (res);
}
