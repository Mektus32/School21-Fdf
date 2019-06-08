/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <ojessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 11:35:36 by ojessi            #+#    #+#             */
/*   Updated: 2019/06/08 16:06:00 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIN_WIDTH		2500
# define WIN_HEIGHT		1300
# define MOVE 350
# define ZOOM 8
# define SPEED 3
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

typedef	struct		s_point
{
	int		x;
	int		y;
	int		z;
}					t_point;

typedef struct		s_mouse
{
	int		ispress;
	int		x;
	int		y;
	int		endX;
	int		endY;
}					t_mouse;

typedef struct		s_image
{
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;
	
}					t_image;

typedef struct		s_map
{
	t_point		**points;
	t_mouse		*mouse;
	t_image		*image;
	void		*mlx_ptr;
	void		*win_ptr;
	int			height;
	int			width;
	int			color;
	int			proj;
	char		*file;
	int			dz;
}					t_map;

typedef struct		s_line
{
	t_point		start;
	t_point		stop;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			err2;
}					t_line;

void				ft_parse_points(t_map *map, char *file);
void				ft_key_hook(t_map *map);
void				ft_print_line(t_map *map, t_line *line);
void				ft_choise_proj(t_map *map);
void				ft_push_coor(t_map *map, char *file);

#endif
