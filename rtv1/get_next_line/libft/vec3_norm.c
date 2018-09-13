/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knedzing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 08:58:53 by knedzing          #+#    #+#             */
/*   Updated: 2018/09/10 15:24:55 by knedzing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec3	vec3_norm(t_vec3 v)
{
	t_vec3	n;
	double	magnitude;

	magnitude = vec3_magnitude(v);
	n.x = v.x / magnitude;
	n.y = v.y / magnitude;
	n.z = v.z / magnitude;
	return (n);
}
