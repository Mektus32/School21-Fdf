/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <ojessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 21:16:51 by ojessi            #+#    #+#             */
/*   Updated: 2019/06/10 16:37:37 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define INDEX ((int)line->start.x + (int)line->start.y * WIN_WIDTH)
#define INDEX2 (x + y * WIN_WIDTH)

void	ft_mouse_one(int x, int y, t_line *line, t_map *map)
{
	while (x != line->stop.x || y != line->stop.y)
	{
		line->f += line->dy * line->sy;
		if (line->f > 0)
		{
			line->f -= line->dx * line->sx;
			y += line->sy;
		}
		x -= line->sx;
		mlx_pixel_put(map->mlx_ptr, map->win_ptr, x, y, map->color);
	}
}

void	ft_mouse_two(int x, int y, t_line *line, t_map *map)
{
	while (x != line->stop.x || y != line->stop.y)
	{
		line->f += line->dx * line->sx;
		if (line->f > 0)
		{
			line->f -= line->dy * line->sy;
			x -= line->sx;
		}
		y += line->sy;
		mlx_pixel_put(map->mlx_ptr, map->win_ptr, x, y, map->color);
	}
}

void	ft_mouse_three(t_map *map)
{
	t_line *line;

	line = ft_memalloc(sizeof(t_line));
	line->start.x = map->mouse->x;
	line->start.y = map->mouse->y;
	line->stop.x = map->mouse->endx;
	line->stop.y = map->mouse->endy;
	ft_print_mouse_line(line, map);
	map->mouse->ispress = 0;
	free(line);
}

void	ft_line_one(int x, int y, t_line *line, int **arr)
{
	while (x != line->stop.x || y != line->stop.y)
	{
		line->f += line->dy * line->sy;
		if (line->f > 0)
		{
			line->f -= line->dx * line->sx;
			y += line->sy;
		}
		x -= line->sx;
		if (!(INDEX2 < 0 || INDEX2 > WIN_WIDTH * WIN_HEIGHT))
			(*arr)[INDEX2] = line->color;
		else
			(*arr)[0] = 0;
	}
}

void	ft_line_two(int x, int y, t_line *line, int **arr)
{
	while (x != line->stop.x || y != line->stop.y)
	{
		line->f += line->dx * line->sx;
		if (line->f > 0)
		{
			line->f -= line->dy * line->sy;
			x -= line->sx;
		}
		y += line->sy;
		if (!(INDEX2 < 0 || INDEX2 > WIN_WIDTH * WIN_HEIGHT))
			(*arr)[INDEX2] = line->color;
		else
			(*arr)[0] = 0;
	}
}
