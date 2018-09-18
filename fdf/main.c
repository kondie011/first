/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knedzing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 15:28:30 by knedzing          #+#    #+#             */
/*   Updated: 2018/07/30 17:53:31 by knedzing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

int			fi(char **line)
{
	int c;

	c = -1;
	while (line[++c])
	{
		free(line[c]);
	}
	free(line);
	return (1);
}

void		get_map(t_mlx *mmlx)
{
	char	*line;
	int		c;
	int		fd;
	char	**map;

	c = 0;
	fd = open(mmlx->file_name, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		c++;
		free(line);
	}
	map = (char**)malloc(sizeof(*map) * (c + 1));
	close(fd);
	fd = open(mmlx->file_name, O_RDONLY);
	c = 0;
	while (get_next_line(fd, &line) == 1)
		map[c++] = line;
	map[c] = NULL;
	mmlx->map = map;
	mmlx->height = c;
}

int			main(int ac, char **av)
{
	t_mlx	*mmlx;

	if (ac == 2)
	{
		mmlx = (t_mlx *)malloc(sizeof(t_mlx));
		mmlx->zoom = 10;
		mmlx->ya = 1;
		mmlx->za = 170;
		mmlx->z = 1;
		mmlx->mlx_ptr = mlx_init();
		mmlx->w_ptr = mlx_new_window(mmlx->mlx_ptr, W, H, "42");
		mmlx->file_name = av[1];
		mmlx->height = 0;
		mmlx->down = H / 2 - mmlx->zoom * (mmlx->height / 2);
		mmlx->right = W / 3;
		put_pix(mmlx);
		mlx_key_hook(mmlx->w_ptr, handle_key_press, mmlx);
		mlx_loop(mmlx->mlx_ptr);
	}
	else
		printf("%s\n", "Error");
	return (0);
}
