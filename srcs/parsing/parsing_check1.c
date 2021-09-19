/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 15:06:33 by threiss           #+#    #+#             */
/*   Updated: 2021/09/18 15:06:35 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	check_range(float nb, float min, float max)
{
	if (nb < min || nb > max)
		return (-1);
	return (1);
}

int	check_vec_range(t_vector *vec, float min, float max)
{
	if (vec->x < min || vec->x > max)
		return (-1);
	if (vec->y < min || vec->y > max)
		return (-1);
	if (vec->z < min || vec->z > max)
		return (-1);
	return (1);
}

int	check_comma(char *str)
{
	int	i;
	int	c;

	i = -1;
	c = 0;
	while (str[++i])
		if (str[i] == ',')
			c++;
	return (c);
}

int	check_vec3(char *line)
{
	char	**split;
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	if (check_comma(line) != 2)
		ret = -1;
	split = ft_split(line, ',');
	while (i < 3)
	{
		if (!ft_is_float(split[i]))
			ret = -1;
		i++;
	}
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (ret);
}

int	check_space(char **split, int x)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	if (i != x)
	{
		free_all(split);
		return (ret_error_msg("Space between/too few data in .rt file!.", -1));
	}
	return (1);
}
