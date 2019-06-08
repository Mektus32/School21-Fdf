/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <ojessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 16:58:40 by ojessi            #+#    #+#             */
/*   Updated: 2019/06/08 18:52:35 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


static	void	move_and_exit(int key, t_map *map)
{
	if (key == 53)
	{
		ft_frtwarr((void**)map->points, map->height);
		exit(0);
	}
	if (key == 126)
	{
		map->ymove -= SPEED;
		map->proj == 1 ? map->xmove -= SPEED : 0;
	}
	if (key == 125)
	{
		map->ymove += SPEED;
		map->proj == 1 ? map->xmove += SPEED : 0;
	}
	if (key == 124)
	{
		map->xmove += SPEED;
		map->proj == 1 ? map->ymove -= SPEED : 0;
	}
	if (key == 123)
	{
		map->xmove -= SPEED;
		map->proj == 1 ? map->ymove += SPEED : 0;
	}
}

static	void	zoom(int key, t_map *map)
{
	
	if (map->dx <= 50 && map->dy <= 50 && key == 32)
	{
		map->dx += 1;
		map->dy += 1;
	}
	if (map->dx >= 2 && map->dy >= 2 && key == 2)
	{
		map->dx -= 1;
		map->dy -= 1;
	}
	key == 13 ? map->dz += 1 : 0;
	key == 6 ? map->dz -= 1 : 0;
}

static	int		keyboard(int key, void *param)
{
	t_map	*map;
	static	int	k = 0;
	
	map = param;
	move_and_exit(key, map);
	if (key == 8)
	{
		if (k % 1 == 0)
			map->color = 0xFFFFFF;//FF0520
		if (k % 2 == 0)
			map->color = 0x0000FF;//23F000
		if (k % 3== 0)
			map->color = 0xFA0022;//0018FA
		k++;
	}
	if (key == 1)
	{
		map->dx = 1;
		map->dz = 1;
		map->dy = 1;
		map->xmove = 1;
		map->ymove = 1;
		map->proj = 0;
		map->color = 0xE805FF;
	}
	if (key == 35)
		map->proj = map->proj == 0 ?  1 : 0;
	zoom(key, map);
	mlx_destroy_image(map->mlx_ptr, map->image->img_ptr);
	ft_choise_proj(map);
	return (0);
}

void				ft_key_hook(t_map *map)
{
	mlx_hook(map->win_ptr, 2, 0, keyboard, map);
}