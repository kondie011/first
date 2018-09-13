/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knedzing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 13:23:30 by knedzing          #+#    #+#             */
/*   Updated: 2018/09/05 13:23:47 by knedzing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *str)
{
	int		sign;
	double	i;
	double	value;

	i = 1;
	sign = 0;
	value = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	*str == '-' ? sign = 1 : 0;
	*str == '-' || *str == '+' ? str++ : 0;
	while ('0' <= *str && *str <= '9')
		value = value * 10 + (*str++ - '0');
	if (*str == '.' && (str++))
		while ('0' <= *str && *str <= '9')
			value += (*str++ - '0') / (i *= 10);
	return (sign == 1 && value > 0 ? -value : value);
}
