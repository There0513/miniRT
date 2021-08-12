/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:20:04 by threiss           #+#    #+#             */
/*   Updated: 2021/08/12 11:33:53 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int check_add_line(char *line, t_all *all) // add struct
{
	int i;

	i = -1;
	if (line[++i] == '#')
		return (0);
	if (line[i] == '\n')
		return (0);
	while (line[i] == ' ')
		i++;
	if (line[i] == 'A')
	{
		if (check_add_ambient(&line[++i], all) == -1)
		{
			printf("error in check_add_ambient\n");
			return (-1); // return error message
		}
	}
	else if (line[i] == 'C')
	{
		if (check_add_camera(&line[++i], all) == -1)
		{
			printf("error in check_add_camera\n");
			return (-1); // return error message
		}
	}
	else if (line[i] == 'L')
	{
		if (check_add_light(&line[++i], all) == -1)
			return (-1); // return error message
	}
	else if (line[i] == 'p' && line[i + 1] == 'l')
	{
		if (check_add_pl(&line[++i], all) == -1)
			return (-1); // return error message
	}
	else if (line[i] == 's' && line[i + 1] == 'p')
	{
		if (check_add_sp(&line[++i], all) == -1)
			return (-1); // return error message
	}
	else if (line[i] == 'c' && line[i + 1] == 'y')
	{
		if (check_add_cy(&line[++i], all) == -1)
			return (-1); // return error message
	}
	else
	{
		printf("why ret -1?!?!\n");
		return (-1);
	}
	return (1);
}

void print_struct(t_all all)
{
	printf("\tPRINT STRUCT\n");
	printf("\tcheckrt\tA = %d C = %d L = %d pl = %d sp = %d cy = %d\n",
		   all.checkrt.A, all.checkrt.C, all.checkrt.L, all.checkrt.pl, all.checkrt.sp, all.checkrt.cy);
	printf("  A\tambient_l = %f\n", all.light.ambient_l);
	printf("\tambient_rgb = %f %f %f\n",
		   all.light.ambient_rgb.x, all.light.ambient_rgb.y, all.light.ambient_rgb.z);
	printf("  C\tpov = %f %f %f\n", all.camera.cam.x, all.camera.cam.y, all.camera.cam.z);
	printf("\torient = %f %f %f fov = %f\n",
		   all.camera.orient.x, all.camera.orient.y, all.camera.orient.z, all.camera.fov);
	printf("  L\tpoint_l = %f %f %f bright_l = %f\n",
		   all.light.point_l.x, all.light.point_l.y, all.light.point_l.z, all.light.bright_l);

	printf(" pl\tvec = %f %f %f  orient = %f %f %f  rgb = %f %f %f\n",
		   all.plane->vec.x, all.plane->vec.y, all.plane->vec.z, all.plane->orient.x, all.plane->orient.y, all.plane->orient.z, all.plane->rgb.x, all.plane->rgb.y, all.plane->rgb.z);
	printf(" sp1\tcenter = %f %f %f  radius = %f  rgb = %f %f %f\n", all.sphere[0].center.x, all.sphere[0].center.y, all.sphere[0].center.z, all.sphere[0].radius, all.sphere[0].rgb.x, all.sphere[0].rgb.y, all.sphere[0].rgb.z);
	printf(" sp2\tcenter = %f %f %f  radius = %f  rgb = %f %f %f\n", all.sphere[1].center.x, all.sphere[1].center.y, all.sphere[1].center.z, all.sphere[1].radius, all.sphere[1].rgb.x, all.sphere[1].rgb.y, all.sphere[1].rgb.z);

	printf(" cy\tvec = %f %f %f  orient = %f %f %f  radius = %f  height = %f  rgb = %f %f %f\n", all.cylinder->vec.x, all.cylinder->vec.y, all.cylinder->vec.z, all.cylinder->orient.x, all.cylinder->orient.y, all.cylinder->orient.z, all.cylinder->radius, all.cylinder->height, all.cylinder->rgb.x, all.cylinder->rgb.y, all.cylinder->rgb.z);
}

int parse_rt(char *file, t_all *all)
{
	int fd;
	char *line;
	int i;

	i = ft_strlen(file);
	if (ft_strncmp(&file[i - 3], ".rt", 3) != 0)
		return (-1);
	// malloc properly
	all->sphere = malloc(3 * sizeof(t_sphere));
	all->plane = malloc(3 * sizeof(t_plane));
	all->cylinder = malloc(3 * sizeof(t_cylinder));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	if (read(fd, NULL, 0) < 0)
	{
		printf("Error read file\n");
		return (0);
	}
	while (get_next_line(fd, &line) == 1)
	{
		if (line[0] != 0)
		{
			if (check_add_line(line, all) == -1) // || A C or L missing
			{
				printf("error in check_add_line\n");
				//print_struct(*all);
				//reinit structs / free if necessary
				return (-1);
			}
		}
		free(line);
	}
	return (1); // if everything is ok -> ret 1
}
