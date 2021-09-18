/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:20:04 by threiss           #+#    #+#             */
/*   Updated: 2021/09/17 22:56:37 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ret_error_msg(char *msg, int ret)
{
	printf("Error\n");
	printf("%s\n", msg);
	return (ret);
}

int	check_add_line3(char *line, t_all *all, int i)
{
	if (line[i] == 'c' && line[i + 1] == 'y')
	{
		if (all->pars == 0)
			return (check_cy(&line[++i], all));
		return (add_cy(&line[++i], all));
	}
	else
		return (ret_error_msg("Check your .rt file, unknown element.", -1));
	return (1);
}

int	check_add_line2(char *line, t_all *all, int i)
{	
	if (line[i] == 'L')
	{
		if (all->pars == 0)
			return (check_light(&line[++i], all));
		return (add_light(&line[++i], all));
	}
	else if (line[i] == 'p' && line[i + 1] == 'l')
	{
		if (all->pars == 0)
			return (check_pl(&line[++i], all));
		return (add_pl(&line[++i], all));
	}
	else if (line[i] == 's' && line[i + 1] == 'p')
	{
		if (all->pars == 0)
			return (check_sp(&line[++i], all));
		return (add_sp(&line[++i], all));
	}
	else
		return (check_add_line3(line, all, i));
}

int	check_add_line(char *line, t_all *all)
{
	int	i;

	i = 0;
	while (ft_is_space(line[i]) == 1)
		i++;
	if (line[i] == '#')
		return (0);
	if (line[i] == '\n')
		return (0);
	if (line[i] == 'A')
	{
		if (all->pars == 0)
			return (check_ambient(&line[++i], all));
		return (add_ambient(&line[++i], all));
	}
	else if (line[i] == 'C')
	{
		if (all->pars == 0)
			return (check_camera(&line[++i], all));
		return (add_camera(&line[++i], all));
	}
	else
		return (check_add_line2(line, all, i));
}

int	checker(int ac, t_all *all, char *file)
{
	if (ac != 2)
		return (ret_error_msg("Please use the program with a .rt file.", 0));
	init_all(all);
	if (parse_rt(file, all) == -1)
		return (ret_error_msg("Parsing error.", 0));
	if (mlx_data_init(&all->mlx, all->width, all->height) != 1)
	{
		free(all->sp);
		free(all->pl);
		free(all->cy);
		return (ret_error_msg("mlx problem.", 0));
	}
	return (1);
}
