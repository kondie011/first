/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_press.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knedzing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 18:04:01 by knedzing          #+#    #+#             */
/*   Updated: 2018/09/14 12:22:34 by knedzing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

void	rotate(int key, t_mlx *mlx)
{
	if (key == 91 || key == 84 || key == 86 || key == 88 ||
			key == 92 || key == 83 || key == 85 || key == 89)
	{
		if (key == 84)
			mlx->cam->angle_x += 2;
		else if (key == 91)
			mlx->cam->angle_x -= 2;
		else if (key == 86)
			mlx->cam->angle_y += 2;
		else if (key == 88)
			mlx->cam->angle_y -= 2;
		else if (key == 83)
			mlx->cam->angle_z += 2;
		else if (key == 92)
			mlx->cam->angle_z -= 2;
		else if (key == 85)
			mlx->cam->angle_w += 2;
		else if (key == 89)
			mlx->cam->angle_w -= 2;
		mlx_clear_window(mlx->mlx, mlx->win);
		ray_trace(mlx);
	}
}

void	zoom(int key, t_mlx *mlx)
{
	if (key == 69 || key == 78)
	{
		if (key == 69)
			mlx->cam->pos.z += 1;
		else if (key == 78)
			mlx->cam->pos.z -= 1;
		mlx_clear_window(mlx->mlx, mlx->win);
		ray_trace(mlx);
	}
}

int		handle_key_press(int key, t_mlx *mlx)
{
	ft_putnbr(key);
	ft_putendl("");
	if (key == 53)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	zoom(key, mlx);
	rotate(key, mlx);
	return (0);
}
