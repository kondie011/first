/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knedzing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 08:56:26 by knedzing          #+#    #+#             */
/*   Updated: 2018/09/13 14:21:24 by knedzing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

void        put_pixel(t_mlx *mlx, int x, int y, t_vec3 col)
{
	int pos;

	if (x >= 0 && y >= 0 && x < W && y < H)
	{
		pos = (x * mlx->bpp) + (y * mlx->sl);
		*(unsigned int *)(mlx->dat + pos) = col.z * 255;
		*(unsigned int *)(mlx->dat + pos + 1) = col.y * 255;
		*(unsigned int *)(mlx->dat + pos + 2) = col.x * 255;
	}
}

void		init_cam(t_cam *cam)
{
	double	small;

	if (W < H)
		small = W;
	else
		small = H;
	cam->w = W / small;
	cam->h = H / small;
	cam->dist = 1.0 / tan(cam->fov / 2.0 * DEG2RAD);
	cam->origin = vec3_sub(vec3_add(vec3_fmul(cam->dir, cam->dist),
				vec3_fmul(vec3_up(), cam->h / 2.0)),
			vec3_fmul(vec3_right(), cam->w / 2.0));
	cam->xi = cam->w / (double)W;
	cam->yi = cam->h / (double)H;
	vec3_rot(&cam->origin, 'x', cam->angle_x);
    vec3_rot(&cam->origin, 'y', cam->angle_y);
    vec3_rot(&cam->origin, 'z', cam->angle_z);
	vec3_rot(&cam->origin, 'w', cam->angle_w);
}

void		ray_trace(t_mlx *mlx)
{
	t_ray *ray;

	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx->dat = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->sl, &mlx->endian);
	mlx->bpp /= 8;
	init_cam(mlx->cam);
	ray = mlx->ray;
	ray->y = -1;
	while (++ray->y < H)
	{
		ray->x = -1;
		while (++ray->x < W)
		{
			mlx->color = vec3_zero();
			trace_init(mlx);
			trace_draw(mlx);
			put_pixel(mlx, mlx->ray->x, mlx->ray->y, mlx->color);
		}
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
		//mlx_destroy_image(mlx->mlx, mlx->img);
	}
	//mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img);
}

void		trace_color(t_mlx *mlx, t_obj *obj, double *min, double *t)
{
	t_vec3  ambient;
	t_vec3  diffuse;
	t_vec3  specular;
	t_lyt   *lyt;

	lyt = mlx->lyt;
	mlx->color = vec3_zero();
	while (lyt != NULL)
	{
		set_light(mlx, lyt);
		set_normal(mlx, obj);
		set_shadows(mlx, obj, t, min);
		lyt->aten = 1.0 / (1.0 + lyt->linear * *min + lyt->quadratic *
				(*min * *min));
		ambient = vec3_fmul(lyt->color, obj->ambient);
        specular = get_specular(mlx, obj, lyt);
		diffuse = get_diffuse(mlx, obj, lyt);
		mlx->tmp_color = vec3_add(ambient, vec3_add(diffuse, specular));
		mlx->tmp_color = vec3_fmul(mlx->tmp_color, lyt->aten);
		mlx->tmp_color = vec3_fmul(mlx->tmp_color, mlx->shadow);
		mlx->tmp_color = vec3_mul(mlx->tmp_color, obj->color);
		mlx->color = vec3_add(mlx->color, mlx->tmp_color);
		lyt = lyt->next;
	}
	vec3_clamp(&mlx->color, 0, 1);
}

void		trace_draw(t_mlx *mlx)
{
	t_obj   *obj;
	double  min;
	double  t;

	min = INFINITY;
	obj = ray_intersect(mlx, &min, &t);
	if (obj != NULL && min != INFINITY)
	{
		mlx->ray->hit = vec3_add(mlx->ray->pos, vec3_fmul(mlx->ray->dir, min));
		trace_color(mlx, obj, &min, &t);
	}
	else
		mlx->color = vec3_zero();
}

void		trace_init(t_mlx *mlx)
{
	t_vec3	x_mult;
	t_vec3	y_mult;

	mlx->ray->pos = mlx->cam->pos;
	mlx->ray->dir = mlx->cam->origin;
	mlx->ray->hit = vec3_zero();
	x_mult = vec3_fmul(vec3_right(), mlx->cam->xi * mlx->ray->x);
	y_mult = vec3_fmul(vec3_up(), mlx->cam->yi * mlx->ray->y);
	mlx->ray->dir = vec3_add(mlx->ray->dir, vec3_sub(x_mult, y_mult));
}

