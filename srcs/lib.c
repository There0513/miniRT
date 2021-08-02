/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:06:18 by threiss           #+#    #+#             */
/*   Updated: 2021/06/29 14:13:55 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int ft_strlen(const char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char *ft_strdup(const char *str)
{
    char *ptr;
    int i;

    i = 0;
    ptr = malloc((ft_strlen(str) + 1) * sizeof(char));
    if (!ptr)
        return (0);
    while (str[i])
    {
        ptr[i] = str[i];
        i++;
    }
    ptr[i] = '\0';
    return (ptr);
}

char *ft_strjoin(const char *s1, const char *s2)
{
    char *ptr;
    int i;
    int j;

    i = 0;
    j = 0;
    ptr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
    if (!ptr)
        return (0);
    while (s1[i])
    {
        ptr[i] = s1[i];
        i++;
    }
    while (s2[j])
    {
        ptr[i + j] = s2[j];
        j++;
    }
    ptr[i + j] = '\0';
    return (ptr);
}

char *ft_substr(const char *str, int start, int len)
{
    char *ptr;
    int i;

    i = 0;
    if (!str)
        return (0);
    ptr = malloc((len + 1) * sizeof(char));
    if (!ptr)
        return (0);
    if (start >= ft_strlen(str))
        return (ptr);
    while (i < len && str[start])
    {
        ptr[i] = str[start];
        i++;
        start++;
    }
    ptr[i] = '\0';
    return (ptr);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		neg;
	long	res;

	i = 0;
	neg = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i++] - 48;
		if (res * neg > 2147483647)
			return (-1);
		if (res * neg < -2147483648)
			return (0);
	}
	return (res * neg);
}

int		ft_get_words(char const *str, char c)
{
	int		words;
	int		i;

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

char	**ft_split(char const *str, char c)
{
	int		i;
	int		i_res;
	char	**res;
	int		len;

	i = 0;
	i_res = -1;
	res = malloc((ft_get_words(str, c) + 1) * sizeof(char*));
	if (!str || !res)
		return (0);
	while (str[i] && ft_get_words(str, c) > 0)
	{
		len = 0;
		while (str[i] == c || (str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
			i++;
		while (str[i] && str[i] != c && !(str[i] >= 9 && str[i] <= 13)) // c = 32
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;

	if (n == 0)
		return (0);
	while (((unsigned char *)s1)[i] && ((unsigned char *)s2)[i] && ((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}