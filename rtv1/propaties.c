/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   propaties.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knedzing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 10:52:15 by knedzing          #+#    #+#             */
/*   Updated: 2018/09/15 13:13:21 by knedzing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

void	set_light(t_mlx *mlx, t_lyt *lyt)
{
	mlx->ray->pos = lyt->pos;
	mlx->ray->dir = vec3_sub(mlx->ray->hit, lyt->pos);
	vec3_normalize(&mlx->ray->dir);
}

void	set_shadows(t_mlx *mlx, t_obj *obj, double *t, double *min)
{
	mlx->shadow = 1.0;
	*min = INFINITY;
	if (ray_intersect(mlx, min, t) != obj)
		mlx->shadow = 0.5;
}

void	set_normal(t_mlx *mlx, t_obj *obj)
{
	if (ft_strequ(obj->type, "plane"))
		obj->normal = vec3_sub(obj->pos, obj->dir);
	else if (ft_strequ(obj->type, "sphere"))
		obj->normal = vec3_sub(obj->pos, mlx->ray->hit);
	else if (ft_strequ(obj->type, "cylinder") || ft_strequ(obj->type, "cone"))
		obj->normal = vec3(obj->pos.x - mlx->ray->hit.x, 0.0,
				obj->pos.z - mlx->ray->hit.z);
	vec3_normalize(&obj->normal);
}

t_vec3	get_diffuse(t_mlx *mlx, t_obj *obj, t_lyt *lyt)
{
	double	diffuse;

	diffuse = vec3_dot(mlx->ray->dir, obj->normal);
	if (diffuse < 0.0)
		diffuse = 0.0;
	return (vec3_fmul(lyt->color, diffuse * obj->diffuse));
}

t_vec3	get_specular(t_mlx *mlx, t_obj *obj, t_lyt *lyt)
{
	t_vec3	lytdir;
	t_vec3	viewdir;
	t_vec3	halfdir;
	double	specular;

	lytdir = vec3_norm(vec3_sub(lyt->pos, mlx->ray->hit));
	viewdir = vec3_norm(vec3_sub(mlx->cam->pos, mlx->ray->hit));
	halfdir = vec3_norm(vec3_add(lytdir, viewdir));
	specular = pow(vec3_dot(obj->normal, halfdir), obj->shine);
	return (vec3_fmul(lyt->color, specular * obj->specular));
}
