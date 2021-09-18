/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 09:58:04 by threiss           #+#    #+#             */
/*   Updated: 2021/09/18 20:01:36 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_str_is_digit(char *str)
{
	int	i;

	i = -1;
	if (str[++i] == '-')
		i++;
	while (i < ft_strlen(str))
		if (!ft_is_digit(str[i++]))
			return (0);
	return (1);
}

int	ft_is_float(char *str)
{
	int	i;

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
