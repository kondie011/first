/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knedzing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 16:46:42 by knedzing          #+#    #+#             */
/*   Updated: 2018/09/14 12:59:02 by knedzing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

void	free_2d(char **str)
{
	int c;

	c = -1;
	while (str[++c])
	{
		free(str[c]);
	}
	free(str);
}

void	get_vec(char *sub, t_vec3 *vec)
{
	char	**split;
	int		c;

	sub[ft_strlen(sub) - 2] = '\0';
	c = -1;
	split = ft_strsplit(sub, ',');
	while (split[++c])
	{
		if (c == 0)
			vec->x = ft_atof(split[0]);
		else if (c == 1)
			vec->y = ft_atof(split[1]);
		else if (c == 2)
			vec->z = ft_atof(split[2]);
	}
	free_2d(split);
}

void	get_cam(int fd, t_cam *cam)
{
	char	*line;

	while (get_next_line(fd, &line) == 1 && ft_strcmp(line, "}"))
	{
		if (ft_strstr(line, "pos"))
			get_vec(ft_strstr(line, "{") + 2, &cam->pos);
		else if (ft_strstr(line, "fov"))
			cam->fov = ft_atof(ft_strstr(line, "= ") + 1);
		else if (ft_strstr(line, "gamma"))
			cam->gamma = ft_atof(ft_strstr(line, "= ") + 1);
		free(line);
	}
	cam->dir = (t_vec3) { 0.0, 0.0, 1.0 };
	free(line);
}

void	finish_it(char *line, t_lyt *lyt, t_obj *obj, t_mlx *mlx)
{
	free(line);
	obj->next = NULL;
	lyt->next = NULL;
	obj = mlx->obj;
	lyt = mlx->lyt;
	mlx->obj = mlx->obj->next;
	mlx->lyt = mlx->lyt->next;
	free(obj);
	free(lyt);
}

void	get_scene(t_mlx *mlx)
{
	int		fd;
	char	*line;
	t_obj	*obj;
	t_lyt	*lyt;

	obj = mlx->obj;
	lyt = mlx->lyt;
	if ((fd = open(mlx->f_n, O_RDONLY)) < 0)
		exit(0);
	while (get_next_line(fd, &line) == 1)
	{
		if (!ft_strcmp(line, "light") && (lyt->next = get_lyt(fd)))
			lyt = lyt->next;
		else if (!ft_strcmp(line, "object") && (obj->next = get_obj(fd)))
			obj = obj->next;
		else if (ft_strequ(line, "camera"))
			get_cam(fd, mlx->cam);
		free(line);
	}
	finish_it(line, lyt, obj, mlx);
}
