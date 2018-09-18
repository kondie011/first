/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knedzing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 15:12:38 by knedzing          #+#    #+#             */
/*   Updated: 2018/09/15 12:43:25 by knedzing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

void	init(t_mlx *mlx)
{
	if (!(mlx->obj = (t_obj*)malloc(sizeof(t_obj))))
		exit(0);
	if (!(mlx->lyt = (t_lyt*)malloc(sizeof(t_lyt))))
		exit(0);
	if (!(mlx->cam = (t_cam*)malloc(sizeof(t_cam))))
		exit(0);
	if (!(mlx->ray = (t_ray*)malloc(sizeof(t_ray))))
		exit(0);
	mlx->obj->next = NULL;
	mlx->lyt->next = NULL;
	mlx->cam->angle_x = 0;
	mlx->cam->angle_y = 0;
	mlx->cam->angle_z = 0;
	mlx->cam->angle_w = 0;
}

int		main(int ac, char **av)
{
	t_mlx		*mlx;

	if (ac >= 2)
	{
		if (!(mlx = (t_mlx*)malloc(sizeof(t_mlx))))
			return (0);
		mlx->mlx = mlx_init();
		mlx->win = mlx_new_window(mlx->mlx, W, H, "RTv1");
		mlx->f_n = av[1];
		init(mlx);
		get_scene(mlx);
		ray_trace(mlx);
		mlx_hook(mlx->win, 2, 0, handle_key_press, mlx);
		mlx_hook(mlx->win, 17, 0, cross, mlx);
		mlx_loop(mlx->mlx);
	}
	else
		write(1, "Error, no scene\n", 16);
	return (0);
}
