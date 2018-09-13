/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knedzing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 13:31:36 by knedzing          #+#    #+#             */
/*   Updated: 2018/09/05 13:32:59 by knedzing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi_base(char *str, int base)
{
	int i;
	int e;
	int res;

	i = ft_strlen(str);
	e = 1;
	res = 0;
	while (--i >= 0)
	{
		if ('0' <= str[i] && str[i] <= '0' + base - 1)
			res += (str[i] - '0') * e;
		if ('A' <= str[i] && str[i] <= 'A' + base - 11)
			res += (str[i] - 'A' + 10) * e;
		e *= base;
	}
	str[0] == '-' && base == 10 ? res *= -1 : 0;
	return (res);
}
