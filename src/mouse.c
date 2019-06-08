/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <ojessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 20:12:31 by ojessi            #+#    #+#             */
/*   Updated: 2019/06/08 22:07:36 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		mouse_press(int	button, int x, int y, void *param)
{
	t_map	*map;
	
	map = param;
	if (map->mouse == NULL)
	{
		map->mouse = ft_memalloc(sizeof(t_mouse));
		map->mouse->anglex = 0;
		map->mouse->angley = 0;
		map->mouse->anglez = 0;
	}
	if (button == 1)
	{
		map->mouse->x = x;
		map->mouse->y = y;
		map->mouse->ispress = 1;
	}
	if (button == 2)
	{
		map->mouse->endX = x;
		map->mouse->endY = y;
		if (map->mouse->ispress == 1)
		{
			ft_print_mouse_line(map->mouse->x, map->mouse->y, map->mouse->endX,
			map->mouse->endY, map);
			map->mouse->ispress = 0;
		}
	}
	return (0);
}

static	void	x_rotation(int x, int *y, int *z, t_map *map)
{
	int		tmpx;
	int		tmpy;
	int		tmpz;

	tmpx = x;
	tmpy = *y;
	tmpz = *z;

	x = tmpx;
	*y = (double)tmpy * cos(map->mouse->anglex) + (double)tmpz * sin(map->mouse->anglex);
	*z = (double)-tmpy * sin(map->mouse->anglex) + (double)tmpz * cos(map->mouse->anglex);
}

static	void	y_rotation(int *x, int y, int *z, t_map *map)
{
	int		tmpx;
	int		tmpy;
	int		tmpz;

	tmpx = *x;
	tmpy = y;
	tmpz = *z;

	*x = (double)tmpx * cos(map->mouse->angley) + (double)tmpz * sin(map->mouse->angley);
	y = tmpy;
	*z = (double)-tmpx * sin(map->mouse->angley) + (double)tmpz * cos(map->mouse->angley);
}

static	void	z_rotation(int *x, int *y, int z, t_map *map)
{
	int		tmpx;
	int		tmpy;
	int		tmpz;

	tmpx = *x;
	tmpy = *y;
	tmpz = z;

	*x = (double)tmpx * cos(map->mouse->anglez) - (double)tmpy * sin(map->mouse->anglez);
	*y = (double)tmpx * sin(map->mouse->anglez) + (double)tmpy * cos(map->mouse->anglez);
	z = tmpy;
}

int		rotation(int key, void *param)
{
	t_map	*map;
	int		i;
	int		j;

	map = param;
	if (map->points3d == NULL)
	{
		map->points3d = ft_memalloc(sizeof(t_point*) * map->height);
		i = -1;
		while (++i < map->height)
			map->points3d[i] = ft_memalloc(sizeof(t_point) * map->width);
		i = -1;
		while (++i < map->height)
		{
			j = -1;
			while (++j < map->width)
			{
				map->points3d[i][j].x = map->points[i][j].x;
				map->points3d[i][j].y = map->points[i][j].y;
				map->points3d[i][j].z = map->points[i][j].z;
			}
		}
	}
	if (map->mouse == NULL)
	{
		map->mouse = ft_memalloc(sizeof(t_mouse));
		map->mouse->anglex = 0;
		map->mouse->angley = 0;
		map->mouse->anglez = 0;
	}
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			if (key == 17)
			{
				y_rotation(&map->points3d[i][j].x, map->points3d[i][j].y,
				&map->points3d[i][j].z, map);
				map->mouse->angley++;
			}
			if (key == 37)
			{
				x_rotation(map->points3d[i][j].x, &map->points3d[i][j].y,
				&map->points3d[i][j].z, map);
				map->mouse->anglex++;
			}
			if (key == 15)
			{
				z_rotation(&map->points3d[i][j].x, &map->points3d[i][j].y,
				map->points3d[i][j].z, map);
				map->mouse->anglez++;
			}
		}
	}
	return (0);
}