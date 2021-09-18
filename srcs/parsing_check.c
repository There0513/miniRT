/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:18:54 by threiss           #+#    #+#             */
/*   Updated: 2021/09/18 14:56:57 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_color(char *line)
{
	int			i;
	char		**split;
	int			ret;
	t_vector	tmp;

	ret = 0;
	i = -1;
	split = ft_split(line, ',');
	if (!ft_is_digit(line[++i]))
		ret = -1;
	if (check_comma(line) != 2)
		ret = -1;
	while (i < 3)
		if (!ft_str_is_digit(split[i++]))
			ret = -1;
	tmp = create_vec(ft_atof(split[0]), ft_atof(split[1]), ft_atof(split[2]));
	if (check_vec_range(&tmp, 0.0, 255.0) == -1)
		ret = -1;
	free_all(split);
	return (ret);
}

int	check_ambient(char *line, t_all *all)
{
	char	**split;
	int		ret;

	ret = 0;
	if (all->checkrt.a)
		ret = -1;
	all->checkrt.a = 1;
	split = ft_split(line, ' ');
	if (check_space(split, 2) != 1)
		return (-1);
	if (!ft_is_float(split[0]))
		ret = -1;
	if (!check_range(ft_atof(split[0]), 0.0, 1.0))
		ret = -1;
	if (check_color(split[1]) == -1)
		ret = -1;
	free_all(split);
	return (ret);
}

int	check_camera2(char **split)
{
	char		**split2;
	int			ret;
	t_vector	tmp;

	ret = 0;
	split2 = ft_split(split[1], ',');
	tmp = create_vec(ft_atof(split2[0]), ft_atof(split2[1]),
			ft_atof(split2[2]));
	if (check_vec_range(&tmp, -1, 1) == -1)
		ret = -1;
	if (!ft_str_is_digit(split[2]))
		ret = -1;
	if (ft_atoi(split[2]) < 0 || ft_atoi(split[2]) > 180)
		ret = -1;
	free_all(split2);
	return (ret);
}

int	check_camera(char *line, t_all *all)
{
	char		**split;
	int			ret;

	ret = 0;
	if (all->checkrt.c)
		ret = -1;
	all->checkrt.c = 1;
	split = ft_split(line, ' ');
	if (check_space(split, 3) != 1)
		return (-1);
	if (check_vec3(split[0]) == -1)
		ret = -1;
	if (check_vec3(split[1]) == -1)
		ret = -1;
	ret = check_camera2(split);
	free_all(split);
	return (ret);
}

int	check_light(char *line, t_all *all)
{
	char	**split;
	int		ret;

	ret = 0;
	if (all->checkrt.l)
		ret = -1;
	all->checkrt.l = 1;
	split = ft_split(line, ' ');
	if (check_space(split, 3) != 1)
		return (-1);
	if (check_vec3(split[0]) == -1)
		ret = -1;
	if (!ft_is_float(split[1]))
		ret = -1;
	if (ft_atof(split[1]) < 0 || ft_atof(split[1]) > 1)
		ret = -1;
	free_all(split);
	return (ret);
}
