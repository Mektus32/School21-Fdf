/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <ojessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:06:21 by ojessi            #+#    #+#             */
/*   Updated: 2019/06/07 20:44:18 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define INDEX (line->start.x + line->start.y * WIN_WIDTH)
#define INDEX2 (x + y * WIN_WIDTH)

void	ft_print_line(t_map *map, t_line *line)
{
	int		*arr;
	int		sign;
	int		f;
	int		x;
	int		y;

	line->start.x += MOVE;
	line->start.y += MOVE;
	line->stop.x += MOVE;
	line->stop.y += MOVE;
	line->dy = line->stop.y - line->start.y;
	line->dx = line->start.x - line->stop.x;
	sign = abs(line->dy) > abs(line->dx) ? 1 : -1;
	line->sy = line->dy < 0 ? -1 : 1;
	line->sx = line->dx < 0 ? -1 : 1;
	f = 0;
	arr = (int*)map->image->img_data;
	arr[INDEX < 0 || INDEX > WIN_WIDTH * WIN_HEIGHT ? 0 : INDEX] = INDEX < 0 || INDEX > WIN_WIDTH * WIN_HEIGHT ? 0 : map->color;
	x = line->start.x;
	y = line->start.y;
	if (sign == -1) 
	{
		while (x != line->stop.x || y != line->stop.y)
		{
			f += line->dy * line->sy;
			if (f > 0)
			{
				f -= line->dx * line->sx;
				y += line->sy;
			}
			x -= line->sx;
			arr[INDEX2 < 0 || INDEX2 > WIN_WIDTH * WIN_HEIGHT ? 0 : INDEX2] = map->color;
		} 
	}
	else
	{
		while (x != line->stop.x || y != line->stop.y)
		{
			f += line->dx * line->sx;
			if (f > 0) {
				f -= line->dy * line->sy;
				x -= line->sx;
			}
			y += line->sy;
			arr[INDEX2 < 0 || INDEX2 > WIN_WIDTH * WIN_HEIGHT ? 0 : INDEX2] = map->color;
		} 
	}
}