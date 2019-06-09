/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <ojessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 20:12:31 by ojessi            #+#    #+#             */
/*   Updated: 2019/06/09 22:07:36 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				mouse_press(int button, int x, int y, void *param)
{
	t_map	*map;

	map = param;
	if (map->mouse == NULL)
		map->mouse = ft_memalloc(sizeof(t_mouse));
	if (button == 1)
	{
		map->mouse->x = x;
		map->mouse->y = y;
		map->mouse->ispress = 1;
	}
	if (button == 2)
	{
		map->mouse->endx = x;
		map->mouse->endy = y;
		if (map->mouse->ispress == 1)
			ft_mouse_three(map);
	}
	return (0);
}

static	void	rotation_x(int i, int j, int key, t_map *map)
{
	if (key == 18)
	{
		map->mouse->angel = 0.05;
		x_rotation(map->points3d[i][j].x, &map->points3d[i][j].y,
		&map->points3d[i][j].z, map);
	}
	if (key == 19)
	{
		map->mouse->angel = -0.05;
		x_rotation(map->points3d[i][j].x, &map->points3d[i][j].y,
		&map->points3d[i][j].z, map);
	}
}

static	void	rotation_y(int i, int j, int key, t_map *map)
{
	if (key == 20)
	{
		map->mouse->angel = 0.05;
		y_rotation(&map->points3d[i][j].x, map->points3d[i][j].y,
		&map->points3d[i][j].z, map);
	}
	if (key == 21)
	{
		map->mouse->angel = -0.05;
		y_rotation(&map->points3d[i][j].x, map->points3d[i][j].y,
		&map->points3d[i][j].z, map);
	}
}

static	void	rotation_z(int i, int j, int key, t_map *map)
{
	if (key == 23)
	{
		map->mouse->angel = 0.05;
		z_rotation(&map->points3d[i][j].x, &map->points3d[i][j].y,
		map->points3d[i][j].z, map);
	}
	if (key == 22)
	{
		map->mouse->angel = -0.05;
		z_rotation(&map->points3d[i][j].x, &map->points3d[i][j].y,
		map->points3d[i][j].z, map);
	}
}

int				rotation(int key, void *param)
{
	t_map	*map;
	int		i;
	int		j;

	map = param;
	ft_init_3d_and_mouse(map);
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			key == 18 || key == 19 ? rotation_x(i, j, key, map) : 0;
			key == 20 || key == 21 ? rotation_y(i, j, key, map) : 0;
			key == 22 || key == 23 ? rotation_z(i, j, key, map) : 0;
		}
	}
	return (0);
}
