/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:40:25 by threiss           #+#    #+#             */
/*   Updated: 2021/09/18 19:09:04 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (((unsigned char *)s1)[i] && ((unsigned char *)s2)[i] &&
			((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
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

void	free_all(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

float	ft_atof(char *str)
{
	t_atof	tab;
	int		i;

	tab.nb = 0.0;
	tab.neg = 1;
	tab.div = 0.1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			tab.neg = -1;
	while (str[i] >= '0' && str[i] <= '9')
		tab.nb = tab.nb * 10 + str[i++] - 48;
	if (str[i] == '.')
	{
		while (str[++i] >= '0' && str[i] <= '9')
		{
			tab.nb = tab.nb + (tab.div * (str[i] - 48));
			tab.div *= 0.1;
		}
	}
	return (tab.nb * tab.neg);
}

int	ft_is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
