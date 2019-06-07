/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <ojessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 16:58:40 by ojessi            #+#    #+#             */
/*   Updated: 2019/06/07 22:04:57 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	int		keyboard(int key, void *param)
{
	t_map	*map;
	int		i;
	int		j;
	static	int	k = 0;
	
	map = param;
	if (key == 53)
		exit(0);
	if (key == 123 || key == 124 || key == 125 || key == 126 || key == 32
	|| key == 2 || key == 13 || key == 6)
	{
		i = -1;
		while (++i < map->height)
		{
			j = -1;
			while (++j < map->width)
			{
				if (key == 126)
				{
					map->points[i][j].y -= SPEED;
					map->proj == 1 ? map->points[i][j].x -= SPEED : 0;
				}
				if (key == 125)
				{
					map->points[i][j].y += SPEED;
					map->proj == 1 ? map->points[i][j].x += SPEED : 0;
				}
				if (key == 124)
				{
					map->points[i][j].x += SPEED;
					map->proj == 1 ? map->points[i][j].y -= SPEED : 0;
				}
				if (key == 123)
				{
					map->points[i][j].x -= SPEED;
					map->proj == 1 ? map->points[i][j].y += SPEED : 0;
				}
				key == 32 ? map->points[i][j].x *= 1.03 : 0;
				key == 32 ? map->points[i][j].y *= 1.03 : 0;
				key == 2 ? map->points[i][j].x *= 0.99 : 0;
				key == 2 ? map->points[i][j].y *= 0.99 : 0;
				key == 6 && map->points[i][j].z / 1.1 > 4 ? map->points[i][j].z /= 1.1 : 0;
				key == 13 && map->points[i][j].z > 3 ? map->points[i][j].z *= 1.1 : 0;
			}
		}
	}
	if (key == 8)
	{
		if (k == 0)
		{
			map->color = 0xFFFFFF;//FF0520
			k++;
		}
		else if (k == 1)
		{
			map->color = 0x0000FF;//23F000
			k++;
		}
		else if (k == 2)
		{
			map->color = 0xFA0022;//0018FA
			k = 0;
		}
	}
	if (key == 1)
	{
		ft_push_coor(map, map->file);
		return (0);
	}
	if (key == 35)
		map->proj = map->proj == 0 ?  1 : 0;
	ft_putnbr(key);
	mlx_destroy_image(map->mlx_ptr, map->image->img_ptr);
	free(map->image);
	ft_choise_proj(map);
	return (0);
}

void				ft_key_hook(t_map *map)
{
	mlx_hook(map->win_ptr, 2, 0, keyboard, map);
}