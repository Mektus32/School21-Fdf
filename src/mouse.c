/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <ojessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 20:12:31 by ojessi            #+#    #+#             */
/*   Updated: 2019/06/09 17:02:27 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		mouse_press(int	button, int x, int y, void *param)
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

static	void	x_rotation(double x, double *y, double *z)
{
	int			tmpx;
	double		tmpy;
	double		tmpz;

	tmpx = x;
	tmpy = *y;
	tmpz = *z;

	x = tmpx;
	*y = (double)tmpy * cos(0.05) + (double)tmpz * sin(0.05);
	*z = (double)-tmpy * sin(0.05) + (double)tmpz * cos(0.05);
}

static	void	y_rotation(double *x, double y, double *z)
{
	double		tmpx;
	int			tmpy;
	double		tmpz;

	tmpx = *x;
	tmpy = y;
	tmpz = *z;

	*x = (double)tmpx * cos(0.05) + (double)tmpz * sin(0.05);
	y = tmpy;
	*z = (double)-tmpx * sin(0.05) + (double)tmpz * cos(0.05);
}

static	void	z_rotation(double *x, double *y, double z)
{
	double		tmpx;
	double		tmpy;
	int			tmpz;

	tmpx = *x;
	tmpy = *y;
	tmpz = z;

	*x = (double)tmpx * cos(0.05) - (double)tmpy * sin(0.05);
	*y = (double)tmpx * sin(0.05) + (double)tmpy * cos(0.05);
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
		map->mouse = ft_memalloc(sizeof(t_mouse));
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			if (key == 17)
			{
				y_rotation(&map->points3d[i][j].x, map->points3d[i][j].y,
				&map->points3d[i][j].z);
			}
			if (key == 37)
			{
				x_rotation(map->points3d[i][j].x, &map->points3d[i][j].y,
				&map->points3d[i][j].z);
			}
			if (key == 15)
			{
				z_rotation(&map->points3d[i][j].x, &map->points3d[i][j].y,
				map->points3d[i][j].z);
			}
		}
	}
	return (0);
}