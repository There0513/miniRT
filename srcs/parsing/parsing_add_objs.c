/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_add_objs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:23:50 by threiss           #+#    #+#             */
/*   Updated: 2021/09/18 19:32:58 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	add_pl(char *line, t_all *all)
{
	char	**split;
	char	**rgb;
	int		ret;
	int		i;

	i = all->checkrt.add_pl;
	ret = 0;
	split = ft_split(line, ' ');
	add_vec3(&all->pl[i].vec, split[1]);
	add_vec3(&all->pl[i].orient, split[2]);
	rgb = ft_split(split[3], ',');
	all->pl[i].rgb.x = ft_atof(rgb[0]);
	all->pl[i].rgb.y = ft_atof(rgb[1]);
	all->pl[i].rgb.z = ft_atof(rgb[2]);
	free_all(split);
	free_all(rgb);
	all->checkrt.add_pl++;
	return (ret);
}

int	add_sp(char *line, t_all *all)
{
	char	**split;
	char	**rgb;
	int		ret;
	int		i;

	i = all->checkrt.add_sp;
	ret = 0;
	split = ft_split(line, ' ');
	add_vec3(&all->sp[i].center, split[1]);
	all->sp[i].radius = ft_atof(split[2]) / 2;
	rgb = ft_split(split[3], ',');
	all->sp[i].rgb.x = ft_atof(rgb[0]);
	all->sp[i].rgb.y = ft_atof(rgb[1]);
	all->sp[i].rgb.z = ft_atof(rgb[2]);
	free_all(split);
	free_all(rgb);
	all->checkrt.add_sp++;
	return (ret);
}

int	add_cy(char *line, t_all *all)
{
	char	**split;
	char	**rgb;
	int		ret;
	int		i;

	i = all->checkrt.add_cy;
	ret = 0;
	split = ft_split(line, ' ');
	add_vec3(&all->cy[i].vec, split[1]);
	add_vec3(&all->cy[i].orient, split[2]);
	all->cy[i].radius = ft_atof(split[3]) / 2;
	all->cy[i].height = ft_atof(split[4]);
	rgb = ft_split(split[5], ',');
	all->cy[i].rgb.x = ft_atof(rgb[0]);
	all->cy[i].rgb.y = ft_atof(rgb[1]);
	all->cy[i].rgb.z = ft_atof(rgb[2]);
	free_all(split);
	free_all(rgb);
	all->checkrt.add_cy++;
	return (ret);
}
