/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_press.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knedzing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 18:04:01 by knedzing          #+#    #+#             */
/*   Updated: 2018/07/28 13:21:17 by knedzing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"
#include <stdio.h>

void	handle_zoom(int key, t_mlx *mmlx)
{
	if (key == 69 || key == 78)
	{
		if (key == 69)
			mmlx->zoom = mmlx->zoom + 5;
		else if (mmlx->zoom > 5 && key == 78)
			mmlx->zoom = mmlx->zoom - 5;
		mlx_clear_window(mmlx->mlx_ptr, mmlx->w_ptr);
		put_pix(mmlx);
	}
}

void	handle_movements(int key, t_mlx *mmlx)
{
	if (key == 123 || key == 124 || key == 125 || key == 126)
	{
		if (key == 123)
			mmlx->right -= 20;
		else if (key == 124)
			mmlx->right += 20;
		else if (key == 126)
			mmlx->down -= 20;
		else if (key == 125)
			mmlx->down += 20;
		mlx_clear_window(mmlx->mlx_ptr, mmlx->w_ptr);
		put_pix(mmlx);
	}
}

void	view(int key, t_mlx *mmlx)
{
	if (key == 34)
	{
		mmlx->za = 170;
		mmlx->ya = 1;
		mlx_clear_window(mmlx->mlx_ptr, mmlx->w_ptr);
		put_pix(mmlx);
	}
	else if (key == 35)
	{
		mmlx->za = 0;
		mmlx->ya = 1;
		mlx_clear_window(mmlx->mlx_ptr, mmlx->w_ptr);
		put_pix(mmlx);
	}
}

void	handle_alt(int key, t_mlx *mmlx)
{
	if (key == 116 && mmlx->z < 30)
	{
		mlx_clear_window(mmlx->mlx_ptr, mmlx->w_ptr);
		mmlx->z++;
		put_pix(mmlx);
	}
	else if (key == 121 && mmlx->z > -30)
	{
		mlx_clear_window(mmlx->mlx_ptr, mmlx->w_ptr);
		mmlx->z--;
		put_pix(mmlx);
	}
}

int		handle_key_press(int key, t_mlx *mmlx)
{
	printf("%d\n", key);
	if (key == 53)
	{
		mlx_destroy_window(mmlx->mlx_ptr, mmlx->w_ptr);
		exit(0);
	}
	handle_zoom(key, mmlx);
	handle_movements(key, mmlx);
	handle_alt(key, mmlx);
	view(key, mmlx);
	return (0);
}
