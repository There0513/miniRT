/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:09:12 by threiss           #+#    #+#             */
/*   Updated: 2021/08/23 14:08:44 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <mlx.h>
#include <math.h>

/*
 ** 1080p default resolution
 */

#define WIDTH_DEF 520
#define HEIGHT_DEF 480

typedef struct s_vector
{
	double x;
	double y;
	double z;
} t_vector;

typedef struct s_mlx
{
	void *mlx;
	void *window;
	void *img;
	char *addr;
	int bpp; // bits per pixel
	int ll;	 // line length
	int endian;
} t_mlx;


typedef	struct	s_checkrt
{
	int		A;
	int		C;
	int		L;
	int		pl;
	int		add_pl;
	int		sp;
	int		add_sp;
	int		cy;
	int		add_cy;
}	t_checkrt;

typedef struct s_camera
{
	t_vector cam; // point of view
	t_vector orient;
	double fov;
	t_vector forward;
	t_vector right;
	t_vector up;
} t_camera;

typedef struct s_light
{
	double ambient_l;			// A
	t_vector ambient_rgb;		// A
	t_vector point_l;			// L
	double bright_l;			// L
	t_vector light_rgb;	//bonus	   L
} t_light;

typedef struct s_sphere
{
	t_vector center;
	double radius; // parsing diameter / 2
	t_vector rgb;
} t_sphere;

typedef struct s_plane
{
	t_vector vec;
	t_vector orient;
	t_vector rgb;
} t_plane;

typedef struct s_cylinder
{
	t_vector vec;
	t_vector orient;
	double radius; // parsing diameter / 2
	double height;
	t_vector rgb;
	t_vector	forward;
	t_vector	right;
	t_vector	up;
} t_cylinder;

// typedef struct s_scenes
// {
// 	t_sphere sp; // sphere
// 	struct s_scenes *next;
// } t_list;

typedef	struct	s_closest
{
	t_vector	p_local;
	t_vector	n_local;
}	t_closest;

typedef	struct	s_all
{
	t_mlx		mlx;
	int			pars;	// pars == 0 -> parsing_check	pars == 1 -> parsing_add
	t_checkrt	checkrt;
	t_camera	camera;
	t_light		light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	t_vector	direction;
	double		t_min;
	t_closest	closest;
	char		nearest[50];
	
}				t_all;

void	print_struct(t_all all);
void	init_all(t_all *all);
// PARSING START ___________________________
int parse_rt(char *file, t_all *all);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int check_add_line(char *line, t_all *all);
// 		GNL START _________________________
#define BUFFER_SIZE 1024
int get_next_line(int fd, char **line);
int ft_check_return(char **estatica, char **line, int r, int fd);
int ft_save_line(char **line, char **estatica, int fd);
char *ft_substr(const char *str, int start, int len);
int ft_new_line_in_static(char *str);
char *ft_strjoin(const char *s1, const char *s2);
char *ft_strdup(const char *str);
int ft_strlen(const char *str);
// 		GNL END _________________________
int check_ambient(char *line, t_all *all);
int add_ambient(char *line, t_all *all);
int	check_camera(char *line, t_all *all);
int	add_camera(char *line, t_all *all);
int	check_light(char *line, t_all *all);
int	add_light(char *line, t_all *all);
int	check_pl(char *line, t_all *all);
int	add_pl(char *line, t_all *all);
int	check_sp(char *line, t_all *all);
int	add_sp(char *line, t_all *all);
int	check_cy(char *line, t_all *all);
int	add_cy(char *line, t_all *all);
int	ft_is_digit(int c);
char	**ft_split(char const *str, char c);
int	check_range(float nb, float min, float max);
int	check_vec_range(t_vector *vec, float min, float max);
int	check_comma(char *str);
int	check_color(char *line);
int	check_vec3(char *line);
int	check_add_vec3(t_vector *cam, char *line);
int	check_add_fov(double *fov, char *line);
int ft_str_is_digit(char *str);
int ft_is_float(char *line);
int	ft_atoi(const char *str);
float	ft_atof(char *str);


// PARSING END ____________________________
void mlx_data_init(t_mlx *data, int width, int height);
int intersection_sp(t_vector rayon, t_vector direction, t_sphere sphere, t_vector *P, t_vector *N, double *t);
int intersection_pl(t_vector rayon, t_vector direction, t_plane plane, t_vector *P, t_vector *N, double *t);
int intersection_cy(t_vector camera, t_vector direction, t_cylinder cylinder, t_vector *P, t_vector *N, double *t);
int rgb_to_int(int r, int g, int b);
void my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
double dot(t_vector a, t_vector b);
double getNorm2(t_vector *sphere);
void normalize(t_vector *sphere);
t_vector get_normalized(t_vector sphere);
t_vector add_min_operation(char sign, t_vector a, t_vector b);
t_vector mult_operation(char sign, double nbr, t_vector a);
void init_spheres(t_sphere *sphere, t_sphere *sphere2, t_sphere *sphere3, t_sphere *sphere4, t_sphere *sphere5);
// t_list scenes
// t_list *get_scenes_lst(t_list *scenes, t_all all);
// t_list *ft_create_elem(t_sphere *sphere);
// t_list *add_elem(t_list *scenes, t_sphere sphere);
void init_dir(t_vector *direction, int x, int y, double fov, t_camera camera);
void camera_rotation(t_camera *camera);
t_vector create_vec(double x, double y, double z);
void	get_closest_t(t_all *all, t_vector *P, t_vector *N, double *t_min);
void	cylinder_rotation(t_cylinder *cylinder);

#endif
