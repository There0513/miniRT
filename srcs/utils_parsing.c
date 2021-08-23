/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 09:58:04 by threiss           #+#    #+#             */
/*   Updated: 2021/08/23 12:45:35 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

float ft_atof(char *str)
{
	float nb;
	int i;
	float neg;
	float div;

	nb = 0.0;
	i = 0;
	neg = 1;
	div = 0.1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + str[i++] - 48;
	if (str[i] == '.')
	{
		while (str[++i] >= '0' && str[i] <= '9')
		{
			nb = nb + (div * (str[i] - 48));
			div *= 0.1;
		}
	}
	return (nb * neg);
}

int ft_str_is_digit(char *str)
{
	int i;

	i = -1;
	if (str[++i] == '-')
		i++;
	while (i < ft_strlen(str))
		if (!ft_is_digit(str[i++]))
			return (0);
	return (1);
}

int ft_is_float(char *str)
{
	int i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '-')
		i++;
	while (ft_is_digit(str[i]))
		i++;
	if (str[i] == '.')
		i++;
	while (ft_is_digit(str[i]))
		i++;
	if (i == 0)
		return (0);
	return (1);
}

int ft_is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}