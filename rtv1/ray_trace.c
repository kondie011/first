/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knedzing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 08:56:26 by knedzing          #+#    #+#             */
/*   Updated: 2018/09/14 11:53:42 by knedzing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

void		put_pixel(t_mlx *mlx, int x, int y, t_vec3 col)
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
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img);
}
