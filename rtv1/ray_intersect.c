/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knedzing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 09:43:39 by knedzing          #+#    #+#             */
/*   Updated: 2018/09/15 12:35:45 by knedzing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

double		sphere_inter(t_mlx *mlx, t_obj *obj)
{
	double	a;
	double	v;
	double	c;
	double	d;
	t_vec3	len;

	len = vec3_sub(mlx->ray->pos, obj->pos);
	a = vec3_dot(mlx->ray->dir, mlx->ray->dir);
	v = vec3_dot(len, mlx->ray->dir);
	c = vec3_dot(len, len) - obj->scale;
	d = v * v - a * c;
	if (d < 0)
		return (-1.0);
	return ((-v - sqrt(d)) / a);
}

double		cone_inter(t_mlx *mlx, t_obj *obj)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_vec3	len;

	len = vec3_sub(mlx->ray->pos, obj->pos);
	a = mlx->ray->dir.x * mlx->ray->dir.x - mlx->ray->dir.y * mlx->ray->dir.y +
		mlx->ray->dir.z * mlx->ray->dir.z;
	b = mlx->ray->dir.x * len.x - mlx->ray->dir.y * len.y +
		mlx->ray->dir.z * len.z;
	c = len.x * len.x + len.z * len.z - len.y * len.y;
	d = b * b - a * c;
	if (d < 0)
		return (-1.0);
	return ((-b - sqrt(d)) / a);
}

double		plane_inter(t_mlx *mlx, t_obj *obj)
{
	double	t;
	double	a;

	a = vec3_dot(obj->dir, obj->pos) - vec3_dot(obj->dir, mlx->ray->pos);
	t = a / vec3_dot(obj->dir, mlx->ray->dir);
	if (t < 0)
		return (-1.0);
	return (t);
}

double		cylinder_inter(t_mlx *mlx, t_obj *obj)
{
	double	a;
	double	b;
	double	c;
	double	disc;
	t_vec3	len;

	len = vec3_sub(mlx->ray->pos, obj->pos);
	a = mlx->ray->dir.x * mlx->ray->dir.x + mlx->ray->dir.z * mlx->ray->dir.z;
	b = (mlx->ray->dir.x * len.x + mlx->ray->dir.z * len.z);
	c = len.x * len.x + len.z * len.z - obj->scale;
	disc = b * b - a * c;
	if (disc < 0)
		return (-1.0);
	return ((-b - sqrt(disc)) / a);
}

t_obj		*ray_intersect(t_mlx *mlx, double *tmin, double *t)
{
	t_obj	*obj;
	t_obj	*out;

	obj = mlx->obj;
	out = NULL;
	while (obj != NULL)
	{
		if (ft_strequ(obj->type, "sphere"))
			*t = sphere_inter(mlx, obj);
		else if (ft_strequ(obj->type, "cone"))
			*t = cone_inter(mlx, obj);
		else if (ft_strequ(obj->type, "cylinder"))
			*t = cylinder_inter(mlx, obj);
		else if (ft_strequ(obj->type, "plane"))
			*t = plane_inter(mlx, obj);
		if (*t > 0 && *t < *tmin)
		{
			out = obj;
			*tmin = *t;
		}
		obj = obj->next;
	}
	return (out);
}
