/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knedzing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 17:49:00 by knedzing          #+#    #+#             */
/*   Updated: 2018/07/30 16:48:41 by knedzing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "../get_next_line/get_next_line.h"
# define H 900
# define W 1500

typedef struct		s_draw
{
	int x;
	int y;
	int dx;
	int dy;
	int swp;
	int s1;
	int s2;
	int p;
	int i;
	int x1;
	int x2;
	int y1;
	int y2;
}					t_draw;
typedef	struct		s_mlx
{
	void	*mlx_ptr;
	void	*w_ptr;
	int		zoom;
	char	**map;
	int		height;
	char	*file_name;
	int		p1[3];
	int		p2[3];
	int		down;
	int		right;
	int		s;
	char	**l;
	char	**l1;
	float	z;
	int		ya;
	int		za;
}					t_mlx;
int					fi(char **line);
void				put_pix(t_mlx *mmlx);
void				set_up_x(t_mlx *mmlx, int x, int y);
void				set_up_y(t_mlx *mmlx, int x, int y);
void				hor_lines(t_mlx *mmlx);
void				ver_lines(t_mlx *mmlx);
int					get_sign(int x);
void				init_draw(t_draw *mdraw, t_mlx *mmlx);
void				swap_em(t_draw *mdraw);
void				draw_line(t_mlx *mmlx, int color);
void				get_map(t_mlx *mmlx);
void				handle_zoom(int key, t_mlx *mmlx);
void				handle_movements(int key, t_mlx *mmlx);
void				view(int key, t_mlx *mmlx);
void				handle_alt(int key, t_mlx *mmlx);
int					handle_key_press(int key, t_mlx *mmlx);

#endif
