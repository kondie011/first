/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lyt_and_obj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knedzing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 11:07:00 by knedzing          #+#    #+#             */
/*   Updated: 2018/09/15 10:13:21 by knedzing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

void	ze_obj_ifs(char *line, t_obj *obj)
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
}

void	init_obj(t_obj *obj)
{
	obj->pos = vec3_zero();
	obj->type = "";
	obj->scale = 1;
	obj->color = ft_htoc(ft_atoi_base("0xFFFFFF", 16));
	obj->ambient = 0;
	obj->diffuse = 0;
	obj->specular = 0;
	obj->shine = 0;
	obj->dir = vec3_zero();
}

t_obj	*get_obj(int fd)
{
	t_obj	*obj;
	char	*line;

	obj = (t_obj*)malloc(sizeof(t_obj));
	init_obj(obj);
	while (get_next_line(fd, &line) == 1 && ft_strcmp(line, "}"))
	{
		ze_obj_ifs(line, obj);
		if (!ft_strstr(line, "type"))
			free(line);
	}
	free(line);
	return (obj);
}

void	init_lyt(t_lyt *lyt)
{
	lyt->pos = vec3_zero();
	lyt->bryt = 0;
	lyt->color = ft_htoc(ft_atoi_base("0xFFFFFF", 16));
	lyt->linear = 0;
	lyt->quadratic = 0;
}

t_lyt	*get_lyt(int fd)
{
	t_lyt	*lyt;
	char	*line;

	lyt = (t_lyt*)malloc(sizeof(t_lyt));
	init_lyt(lyt);
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
		free(line);
	}
	free(line);
	return (lyt);
}
