/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_clamp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knedzing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 18:51:53 by knedzing          #+#    #+#             */
/*   Updated: 2018/09/14 10:32:12 by knedzing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	vec3_clamp(t_vec3 *v, double min, double max)
{
	if (v->x > max)
		v->x = max;
	if (v->y > max)
		v->y = max;
	if (v->z > max)
		v->z = max;
	if (v->x < min)
		v->x = min;
	if (v->y < min)
		v->y = min;
	if (v->z < min)
		v->z = min;
}
