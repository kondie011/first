/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knedzing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 11:32:18 by knedzing          #+#    #+#             */
/*   Updated: 2018/09/14 11:46:41 by knedzing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

void		trace_color(t_mlx *mlx, t_obj *obj, double *min, double *t)
{
	t_vec3	ambient;
	t_vec3	diffuse;
	t_vec3	specular;
	t_lyt	*lyt;

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
	t_obj	*obj;
	double	min;
	double	t;

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
