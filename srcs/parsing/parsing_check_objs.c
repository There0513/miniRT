/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_objs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:26:39 by threiss           #+#    #+#             */
/*   Updated: 2021/09/19 17:27:32 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	check_pl(char *line, t_all *all)
{
	char		**split;
	char		**split2;
	int			ret;
	t_vector	tmp;

	ret = 0;
	all->checkrt.pl++;
	split = ft_split(line, ' ');
	if (check_space(split, 4) != 1)
		return (-1);
	if (check_vec3(split[1]) == -1)
		ret = -1;
	if (check_vec3(split[2]) == -1)
		ret = -1;
	split2 = ft_split(split[2], ',');
	tmp = create_vec(ft_atof(split2[0]), ft_atof(split2[1]),
			ft_atof(split2[2]));
	if (check_vec_range(&tmp, -1, 1) == -1)
		ret = -1;
	if (check_color(split[3]) == -1)
		ret = -1;
	free_all(split);
	free_all(split2);
	return (ret);
}

int	check_sp(char *line, t_all *all)
{
	char	**split;
	int		ret;

	ret = 0;
	all->checkrt.sp++;
	split = ft_split(line, ' ');
	if (check_space(split, 4) != 1)
		return (-1);
	if (check_vec3(split[1]) == -1)
		ret = -1;
	if (!ft_is_float(split[2]))
		ret = -1;
	if (ft_atof(split[2]) < 0.0)
		ret = -1;
	if (check_color(split[3]) == -1)
		ret = -1;
	free_all(split);
	return (ret);
}

int	check_cy2(t_vector tmp, char **split)
{
	int	ret;

	ret = 1;
	if (check_vec_range(&tmp, -1, 1) == -1)
		ret = -1;
	if (!ft_is_float(split[3]))
		ret = -1;
	if (ft_atof(split[3]) < 0.0)
		ret = -1;
	if (!ft_is_float(split[4]))
		ret = -1;
	if (ft_atof(split[4]) < 0.0)
		ret = -1;
	if (check_color(split[5]) == -1)
		ret = -1;
	return (ret);
}

int	check_cy(char *line, t_all *all)
{
	char		**split;
	char		**split2;
	int			ret;
	t_vector	tmp;

	ret = 0;
	all->checkrt.cy++;
	split = ft_split(line, ' ');
	if (check_space(split, 6) != 1)
		return (-1);
	if (check_vec3(split[1]) == -1)
		ret = -1;
	split2 = ft_split(split[2], ',');
	tmp = create_vec(ft_atof(split2[0]), ft_atof(split2[1]),
			ft_atof(split2[2]));
	if (check_cy2(tmp, split) != 1)
		ret = -1;
	free_all(split);
	free_all(split2);
	return (ret);
}
