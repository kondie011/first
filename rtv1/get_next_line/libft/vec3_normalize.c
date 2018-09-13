/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_normalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knedzing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 09:22:18 by knedzing          #+#    #+#             */
/*   Updated: 2018/09/04 09:22:29 by knedzing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	vec3_normalize(t_vec3 *v)
{
	double	magnitude;

	magnitude = vec3_magnitude(*v);
	v->x /= magnitude;
	v->y /= magnitude;
	v->z /= magnitude;
}
