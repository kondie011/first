/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pix.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knedzing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 17:42:25 by knedzing          #+#    #+#             */
/*   Updated: 2018/07/30 16:54:23 by knedzing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

void		set_up_x(t_mlx *mmlx, int x, int y)
{
	mmlx->l = ft_strsplit(mmlx->map[y], ' ');
	if (x == 0 && ft_atoi(mmlx->l[x]) == 0)
		mmlx->p1[2] = 1;
	else if (x == 0 && (mmlx->s = ft_atoi(mmlx->l[x])))
		mmlx->p1[2] = mmlx->s * mmlx->z * get_sign(mmlx->s);
	if (ft_atoi(mmlx->l[x + 1]) == 0)
		mmlx->p2[2] = 1;
	else if ((mmlx->s = ft_atoi(mmlx->l[x + 1])))
		mmlx->p2[2] = mmlx->s * mmlx->z * get_sign(mmlx->s);
	if (fi(mmlx->l) && x == 0)
	{
		mmlx->p1[0] = (x * mmlx->zoom) + mmlx->right;
		mmlx->p1[1] = (y * mmlx->zoom) + mmlx->down;
		mmlx->p1[1] = mmlx->p1[1] * cos(mmlx->ya) - mmlx->p1[2] * sin(mmlx->ya);
		mmlx->p1[0] = mmlx->p1[0] * cos(mmlx->za) - mmlx->p1[1] * sin(mmlx->za);
		mmlx->p1[1] = mmlx->p1[0] * sin(mmlx->za) + mmlx->p1[1] * cos(mmlx->za);
	}
	else if ((mmlx->p1[0] = mmlx->p2[0]) || 1)
		mmlx->p1[1] = mmlx->p2[1];
	mmlx->p2[0] = ((x + 1) * mmlx->zoom) + mmlx->right;
	mmlx->p2[1] = (y * mmlx->zoom) + mmlx->down;
	mmlx->p2[1] = mmlx->p2[1] * cos(mmlx->ya) - mmlx->p2[2] * sin(mmlx->ya);
	mmlx->p2[0] = mmlx->p2[0] * cos(mmlx->za) - mmlx->p2[1] * sin(mmlx->za);
	mmlx->p2[1] = mmlx->p2[0] * sin(mmlx->za) + mmlx->p2[1] * cos(mmlx->za);
}

void		set_up_y(t_mlx *mmlx, int x, int y)
{
	mmlx->l = ft_strsplit(mmlx->map[y], ' ');
	if (y == 0 && ft_atoi(mmlx->l[x]) == 0)
		mmlx->p1[2] = 1;
	else if (y == 0 && (mmlx->s = ft_atoi(mmlx->l[x])))
		mmlx->p1[2] = mmlx->s * mmlx->z * get_sign(mmlx->s);
	fi(mmlx->l);
	if (ft_atoi((mmlx->l = ft_strsplit(mmlx->map[y + 1], ' '))[x]) == 0)
		mmlx->p2[2] = 1;
	else if ((mmlx->s = ft_atoi(mmlx->l[x])))
		mmlx->p2[2] = mmlx->s * mmlx->z * get_sign(mmlx->s);
	if (fi(mmlx->l) && y == 0)
	{
		mmlx->p1[0] = (x * mmlx->zoom) + mmlx->right;
		mmlx->p1[1] = (y * mmlx->zoom) + mmlx->down;
		mmlx->p1[1] = mmlx->p1[1] * cos(mmlx->ya) - mmlx->p1[2] * sin(mmlx->ya);
		mmlx->p1[0] = mmlx->p1[0] * cos(mmlx->za) - mmlx->p1[1] * sin(mmlx->za);
		mmlx->p1[1] = mmlx->p1[0] * sin(mmlx->za) + mmlx->p1[1] * cos(mmlx->za);
	}
	else if ((mmlx->p1[0] = mmlx->p2[0]) || 1)
		mmlx->p1[1] = mmlx->p2[1];
	mmlx->p2[0] = (x * mmlx->zoom) + mmlx->right;
	mmlx->p2[1] = ((y + 1) * mmlx->zoom) + mmlx->down;
	mmlx->p2[1] = mmlx->p2[1] * cos(mmlx->ya) - mmlx->p2[2] * sin(mmlx->ya);
	mmlx->p2[0] = mmlx->p2[0] * cos(mmlx->za) - mmlx->p2[1] * sin(mmlx->za);
	mmlx->p2[1] = mmlx->p2[0] * sin(mmlx->za) + mmlx->p2[1] * cos(mmlx->za);
}

void		hor_lines(t_mlx *mmlx)
{
	int		y;
	int		x;
	char	**line;
	int		c;

	y = -1;
	while (mmlx->map[++y])
	{
		x = -1;
		line = ft_strsplit(mmlx->map[y], ' ');
		while (line[++x] && line[x + 1])
		{
			set_up_x(mmlx, x, y);
			if (ft_atoi(line[x]) != 0 && (c = ft_atoi(line[x + 1])))
				draw_line(mmlx, 0x54F * (abs(c) * fabs(mmlx->z)) + 0xFFF);
			else
				draw_line(mmlx, 0x5544FF);
			free(line[x]);
		}
		free(line[x]);
		free(line);
		free(mmlx->map[y]);
	}
	free(mmlx->map[y]);
	free(mmlx->map);
}

void		ver_lines(t_mlx *mmlx)
{
	int		y;
	int		x;
	char	**line;
	int		c;
	char	**l;

	x = -1;
	line = ft_strsplit(mmlx->map[0], ' ');
	while (line[++x] && (y = -1))
	{
		while (mmlx->map[++y] && mmlx->map[y + 1])
			if ((l = ft_strsplit(mmlx->map[y], ' '))[x] &&
					(mmlx->l1 = ft_strsplit(mmlx->map[y + 1], ' '))[x])
			{
				set_up_y(mmlx, x, y);
				if (ft_atoi(l[x]) != 0 && (c = ft_atoi(mmlx->l1[x])))
					draw_line(mmlx, 0x54F * (abs(c) * fabs(mmlx->z)) + 0xFFF);
				else
					draw_line(mmlx, 0x5544FF);
				fi(mmlx->l1);
				fi(l);
			}
		free(line[x]);
	}
	free(line);
}

void		put_pix(t_mlx *mmlx)
{
	get_map(mmlx);
	ver_lines(mmlx);
	hor_lines(mmlx);
}
