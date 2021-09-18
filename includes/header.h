/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:09:12 by threiss           #+#    #+#             */
/*   Updated: 2021/09/18 17:39:28 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

/*
 **	bpp = bits per pixel
 **	ll = line length
 */
typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}	t_mlx;

typedef struct s_checkrt
{
	int	a;
	int	c;
	int	l;
	int	pl;
	int	add_pl;
	int	sp;
	int	add_sp;
	int	cy;
	int	add_cy;
}	t_checkrt;

typedef struct s_camera
{
	t_vector	cam;
	t_vector	orient;
	double		fov;
	t_vector	forward;
	t_vector	right;
	t_vector	up;
}	t_camera;

typedef struct s_light
{
	double		ambient_l;
	t_vector	ambient_rgb;
	t_vector	point_l;
	double		bright_l;
	t_vector	light_rgb;
}	t_light;

typedef struct s_sphere
{
	t_vector	center;
	double		radius;
	t_vector	rgb;
}	t_sphere;

typedef struct s_plane
{
	t_vector	vec;
	t_vector	orient;
	t_vector	rgb;
}	t_plane;

typedef struct s_cylinder
{
	double		bright;
	double		br;
	t_vector	vec;
	t_vector	orient;
	double		radius;
	double		height;
	t_vector	rgb;
	t_vector	forward;
	t_vector	right;
	t_vector	up;
}	t_cylinder;

typedef struct s_closest
{
	t_vector	p_local;
	t_vector	n_local;
	double		intens;
}	t_closest;

typedef struct visibility
{
	int			i;
	t_vector	dir;
	t_vector	p2;
	double		a;
	double		b;
	t_vector	light_p;
	t_vector	p2_p;
	int			ret;
}	t_visib;

typedef struct intersection
{
	double		a;
	double		b;
	double		c;
	double		delta;
	double		t1;
	double		t2;
	t_vector	oc;
}	t_inters;

/*
 **	int	pars == 0 -> parsing_check
 **	pars == 1 -> parsing_add
 */

typedef	struct atof
{
	float	nb;
	float	neg;
	float	div;
}	t_atof;

typedef struct s_all
{
	int			width;
	int			height;
	t_vector	p;
	t_vector	n;
	t_mlx		mlx;
	int			pars;
	t_checkrt	checkrt;
	t_camera	camera;
	t_light		light;
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
	t_vector	dir;
	double		t_min;
	double		t_tmp;
	double		t_visib;
	t_closest	closest;
	char		nearest[50];
}	t_all;

void		print_struct(t_all all);
void		init_all(t_all *all);
int	key_press(unsigned int key, t_all *all);
int	minim_wind(t_all *all);
// PARSING START ___________________________
int	checker(int ac, t_all *all, char *file);
int			parse_rt(char *file, t_all *all);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			check_add_line(char *line, t_all *all);
// 		GNL START _________________________
# define BUFFER_SIZE 1024

int			get_next_line(int fd, char **line);
int			ft_check_return(char **estatica, char **line, int r, int fd);
int			ft_save_line(char **line, char **estatica, int fd);
char		*ft_substr(const char *str, int start, int len);
int			ft_new_line_in_static(char *str);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strdup(const char *str);
int			ft_strlen(const char *str);
// 		GNL END _________________________
int			check_space(char **split, int x);
int			add_vec3(t_vector *vec, char *line);
int			check_ambient(char *line, t_all *all);
int			add_ambient(char *line, t_all *all);
int			check_camera(char *line, t_all *all);
int			add_camera(char *line, t_all *all);
int			check_light(char *line, t_all *all);
int			add_light(char *line, t_all *all);
int			check_pl(char *line, t_all *all);
int			add_pl(char *line, t_all *all);
int			check_sp(char *line, t_all *all);
int			add_sp(char *line, t_all *all);
int			check_cy(char *line, t_all *all);
int			add_cy(char *line, t_all *all);
int			ft_is_digit(int c);
char		**ft_split(char const *str, char c);
int			check_range(float nb, float min, float max);
int			check_vec_range(t_vector *vec, float min, float max);
int			check_comma(char *str);
int			check_color(char *line);
int			check_vec3(char *line);
int			check_add_vec3(t_vector *cam, char *line);
int			check_add_fov(double *fov, char *line);
int			ft_str_is_digit(char *str);
int			ft_is_float(char *line);
int			ft_atoi(const char *str);
float		ft_atof(char *str);
void		free_all(char **split);
// PARSING END ____________________________
int			mlx_data_init(t_mlx *data, int width, int height);
int			intersection_sp(t_all *all, t_sphere sp);
int			intersection_pl(t_all *all, t_plane pl);
int			intersection_cy(t_all *all, t_cylinder *cy);
int			rgb_to_int(double r, double g, double b, t_all *all);
void		my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
double		dot(t_vector a, t_vector b);
double		get_norm(t_vector *sphere);
void		normalize(t_vector *sphere);
t_vector	get_normalized(t_vector sphere);
t_vector	calc_op(char sign, t_vector a, t_vector b);
t_vector	mult_op(char sign, double nbr, t_vector a);
void		init_dir(t_all *all, t_vector *dir, int x, int y);
void		camera_rotation(t_camera *camera);
t_vector	create_vec(double x, double y, double z);
void		get_closest_t(t_all *all);
void		cylinder_rotation(t_cylinder *cy);
void		cylinder_rotation2(t_cylinder cy);
void		light(t_all *all);
int			shadow_sp(t_all *all, t_sphere sp, t_vector P, t_vector dir);
int			shadow_cy(t_all *all, t_cylinder *cy, t_vector dir);
int			inter_cy(t_all *all, double t12, t_cylinder *cy);
int			shad_cy(t_all *all, double t1, t_vector dir, t_cylinder cy);
int			shadow_pl(t_all *all, t_plane pl, t_vector P, t_vector dir);
void		d_rgb_min_max(double *r, double *g, double *b);
void		rgb_min_max(double *r, double *g, double *b);
int			ft_exit(t_all *all);
int			ft_is_space(char c);
int			ret_error_msg(char *msg, int ret);

#endif
