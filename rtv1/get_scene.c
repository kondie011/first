/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knedzing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 16:46:42 by knedzing          #+#    #+#             */
/*   Updated: 2018/09/13 08:49:32 by knedzing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

void	get_vec(char *sub, t_vec3 *vec)
{
	char    **split;
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
		//free(sub);
		//free(line);
	}
	cam->dir = (t_vec3) { 0.0, 0.0, 1.0 };
	//free(line);
}

t_obj	*get_obj(int fd)
{
	t_obj	*obj;
	char	*line;

	obj = (t_obj*)malloc(sizeof(t_obj));
	while (get_next_line(fd, &line) == 1 && ft_strcmp(line, "}"))
    {
        if (ft_strstr(line, "pos"))
            get_vec(ft_strstr(line, "{") + 2, &obj->pos);
		else if (ft_strstr(line, "type"))
            obj->type = ft_strstr(line, "= ") + 2;
		else if (ft_strstr(line, "scale"))
            obj->scale = ft_atof(ft_strstr(line, "= ") + 1);
        else if (ft_strstr(line, "color"))
            obj->color = ft_htoc(ft_atoi_base(ft_strstr(line, "=") + 1, 16));
        else if (ft_strstr(line, "ambient"))
            obj->ambient = ft_atof(ft_strstr(line, "= ") + 1);
        else if (ft_strstr(line, "diffuse"))
            obj->diffuse = ft_atof(ft_strstr(line, "= ") + 1);
        else if (ft_strstr(line, "specular"))
            obj->specular = ft_atof(ft_strstr(line, "= ") + 1);
        else if (ft_strstr(line, "shininess"))
            obj->shine = ft_atof(ft_strstr(line, "= ") + 1);
        else if (ft_strstr(line, "dir"))
            get_vec(ft_strstr(line, "{") + 2, &obj->dir);
        //free(line);
    }
	return (obj);
}

t_lyt	*get_lyt(int fd)
{
	t_lyt	*lyt;
	char	*line;

	lyt = (t_lyt*)malloc(sizeof(t_lyt));
	lyt->quadratic = 0;
	lyt->linear = 0;
	while (get_next_line(fd, &line) == 1 && ft_strcmp(line, "}"))
    {
        if (ft_strstr(line, "pos"))
            get_vec(ft_strstr(line, "{") + 2, &lyt->pos);
        else if (ft_strstr(line, "intensity"))
            lyt->bryt = ft_atof(ft_strstr(line, "= ") + 1);
        else if (ft_strstr(line, "color"))
            lyt->color = ft_htoc(ft_atoi_base(ft_strstr(line, "= ") + 2, 16));
        else if (ft_strstr(line, "linear"))
            lyt->linear = ft_atof(ft_strstr(line, "= ") + 1);
        else if (ft_strstr(line, "quadratic"))
            lyt->quadratic = ft_atof(ft_strstr(line, "= ") + 1);
        //free(line);
    }
    return (lyt);
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
	get_cam(fd, mlx->cam);
	while (get_next_line(fd, &line) == 1)
	{
        if (!ft_strcmp(line, "light") && (lyt->next = get_lyt(fd)))
            lyt = lyt->next;
		else if (!ft_strcmp(line, "object") && (obj->next = get_obj(fd)))
			obj = obj->next;
	}
	obj->next = NULL;
	lyt->next = NULL;
	mlx->obj = mlx->obj->next;
	mlx->lyt = mlx->lyt->next;
}
