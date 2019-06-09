/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <ojessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:06:21 by ojessi            #+#    #+#             */
/*   Updated: 2019/06/09 16:52:00 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define INDEX ((int)line->start.x + (int)line->start.y * WIN_WIDTH)
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
	if (!(INDEX < 0 || INDEX > WIN_WIDTH * WIN_HEIGHT))
		arr[INDEX] = map->color;
	else
		arr[0] = 0;
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
			if (!(INDEX2 < 0 || INDEX2 > WIN_WIDTH * WIN_HEIGHT))
				arr[INDEX2] = map->color;
			else
				arr[0] = 0;
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
			if (!(INDEX2 < 0 || INDEX2 > WIN_WIDTH * WIN_HEIGHT))
				arr[INDEX2] = map->color;
			else
				arr[0] = 0;
		} 
	}
}

void	ft_print_mouse_line(int x0, int y0, int x1, int y1, t_map *map)
{
  int A, B, sign;
  A = y1 - y0;
  B = x0 - x1;
  if (abs(A) > abs(B)) sign = 1;
  else sign = -1;
  int signa, signb;
  if (A < 0) signa = -1;
  else signa = 1;
  if (B < 0) signb = -1;
  else signb = 1;
  int f = 0;
  mlx_pixel_put(map->mlx_ptr, map->win_ptr, x0, y0, map->color);
  int x = x0, y = y0;
  if (sign == -1) 
  {
    do {
      f += A*signa;
      if (f > 0)
      {
        f -= B*signb;
        y += signa;
      }
      x -= signb;
      mlx_pixel_put(map->mlx_ptr, map->win_ptr, x, y, map->color);
    } while (x != x1 || y != y1);
  }
  else
  {
    do {
      f += B*signb;
      if (f > 0) {
        f -= A*signa;
        x -= signb;
      }
      y += signa;
      mlx_pixel_put(map->mlx_ptr, map->win_ptr, x, y, map->color);
    } while (x != x1 || y != y1);
  }
}