/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knedzing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 15:09:19 by knedzing          #+#    #+#             */
/*   Updated: 2018/09/13 14:20:16 by knedzing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
#define RTV1_H
# define W 900
# define H 900
# define PI 3.1415926
# define DEG2RAD PI / 180
# define RAD2DEG 180 / PI
# include <math.h>
# include <mlx.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../get_next_line/get_next_line.h"

#include <stdio.h>

typedef struct			s_obj
{
	t_vec3			pos;
	t_vec3          normal;
	t_vec3			dir;
	double			scale;
	char			*type;
	double			ambient;
	double			specular;
	double			diffuse;
	double			shine;
	t_vec3			color;
	struct s_obj	*next;
}						t_obj;
typedef struct			s_cam
{
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			rot;
	t_vec3			origin;
	double			dist;
	double			w;
	double			h;
	double			xi;
	double			yi;
	double			fov;
    double          angle_x;
    double          angle_y;
    double          angle_z;
	double			angle_w;
	double			samp_inc;
	double			gamma;
}						t_cam;
typedef struct			s_lyt
{
	t_vec3			pos;
	t_vec3			color;
	double			bryt;
	double			linear;
	double			quadratic;
	double			aten;
	struct s_lyt	*next;
}						t_lyt;
typedef struct			s_ray
{
	t_vec3		pos;
	t_vec3		dir;
	t_vec3		hit;
	double	x;
	double	y;
}						t_ray;
typedef struct			s_draw
{
    double          xyz[3];
	double			g;
	int				f;
	int				m;
    int             s;
    int             h;
    int             w;
}						t_draw;
typedef struct          s_mlx
{
    void            *mlx;
    void            *win;
    void            *img;
    char            *dat;
    int             bpp;
    int             sl;
    int             endian;
    char            *f_n;
    int             **w_map;
    int             width;
    int             height;
	double			shadow;
	t_vec3			color;
    t_vec3          tmp_color;
	t_obj			*obj;
	t_cam			*cam;
	t_lyt			*lyt;
	t_ray			*ray;
	t_draw			*draw;
}                       t_mlx;
t_vec3  get_specular(t_mlx *mlx, t_obj *obj, t_lyt *lyt);
t_vec3  get_diffuse(t_mlx *mlx, t_obj *obj, t_lyt *lyt);
void    set_shadows(t_mlx *mlx, t_obj *obj, double *t, double *min);
void    set_light(t_mlx *mlx, t_lyt *lyt);
void    set_normal(t_mlx *mlx, t_obj *obj);
int     handle_key_press(int key, t_mlx *mlx);
int     cross(int key, t_mlx *mlx);
t_obj	*ray_intersect(t_mlx *mlx, double *a, double *b);
void        ray_trace(t_mlx *mlx);
void	get_scene(t_mlx *mlx);
void        trace_draw(t_mlx *mlx);
void        trace_init(t_mlx *mlx);
#endif
