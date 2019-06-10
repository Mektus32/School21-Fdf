/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <ojessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:06:21 by ojessi            #+#    #+#             */
/*   Updated: 2019/06/10 16:36:00 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define INDEX ((int)line->start.x + (int)line->start.y * WIN_WIDTH)
#define INDEX2 (x + y * WIN_WIDTH)

void	ft_print_line(t_map *map, t_line *line)
{
	int		*arr;
	int		x;
	int		y;

	line->start.x += WIN_WIDTH / 2;
	line->start.y += WIN_HEIGHT / 2;
	line->stop.x += WIN_WIDTH / 2;
	line->stop.y += WIN_HEIGHT / 2;
	line->dy = line->stop.y - line->start.y;
	line->dx = line->start.x - line->stop.x;
	line->sy = line->dy < 0 ? -1 : 1;
	line->sx = line->dx < 0 ? -1 : 1;
	arr = (int*)map->image->img_data;
	line->f = 0;
	line->color = map->color;
	if (!(INDEX < 0 || INDEX > WIN_WIDTH * WIN_HEIGHT))
		arr[INDEX] = line->color;
	else
		arr[0] = 0;
	x = line->start.x;
	y = line->start.y;
	if ((abs(line->dy) > abs(line->dx) ? 1 : -1) == -1)
		ft_line_one(x, y, line, &arr);
	else
		ft_line_two(x, y, line, &arr);
}

void	ft_print_mouse_line(t_line *line, t_map *map)
{
	int		sign;
	int		x;
	int		y;

	line->dy = line->stop.y - line->start.y;
	line->dx = line->start.x - line->stop.x;
	sign = abs(line->dy) > abs(line->dx) ? 1 : -1;
	line->sy = line->dy < 0 ? -1 : 1;
	line->sx = line->dx < 0 ? -1 : 1;
	line->f = 0;
	mlx_pixel_put(map->mlx_ptr, map->win_ptr, line->start.x,
	line->start.y, map->color);
	x = line->start.x;
	y = line->start.y;
	if (sign == -1)
		ft_mouse_one(x, y, line, map);
	else
		ft_mouse_two(x, y, line, map);
}
