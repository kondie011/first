/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_rot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knedzing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 09:23:12 by knedzing          #+#    #+#             */
/*   Updated: 2018/09/14 10:43:37 by knedzing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	do_insane_rot(t_vec3 *rot, t_vec3 *v, double angle)
{
	rot->x = v->x * cos(angle) - v->z * sin(angle);
	rot->y = -v->x * sin(angle) * sin(angle) + v->y * cos(angle) -
		v->z * sin(angle) * cos(angle);
	rot->z = v->x * cos(angle) * sin(angle) + v->y * sin(angle) +
		v->z * cos(angle) * cos(angle);
}

void	vec3_rot(t_vec3 *v, int axis, double angle)
{
	t_vec3	rot;

	angle *= DEG2RAD;
	rot = (t_vec3) { v->x, v->y, v->z };
	if (axis == 'x')
	{
		rot.y = v->y * cos(angle) - v->z * sin(angle);
		rot.z = v->y * sin(angle) + v->z * cos(angle);
	}
	else if (axis == 'y')
	{
		rot.x = v->x * cos(angle) - v->z * sin(angle);
		rot.z = v->x * sin(angle) + v->z * cos(angle);
	}
	else if (axis == 'z')
	{
		rot.x = v->x * cos(angle) - v->y * sin(angle);
		rot.y = v->x * sin(angle) + v->y * cos(angle);
	}
	else if (axis == 'w')
	{
		do_insane_rot(&rot, v, angle);
	}
	*v = rot;
}
