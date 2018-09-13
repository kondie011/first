/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knedzing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 17:18:42 by knedzing          #+#    #+#             */
/*   Updated: 2018/08/25 17:37:01 by knedzing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

double		vec_dot(double *a, double *b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

double		*vec_add(double *a, double *b)
{
	double *c;

	c = (float)malloc(sizeof(double) * 3);
	c[0] = a[0] + b[0];
	c[1] = a[1] + b[1];
	c[2] = a[2] + b[2];
	return (c);
}

double		*vec_cross(double *a, double *b)
{
	//double	
}
