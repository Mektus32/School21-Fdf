/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <ojessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 16:58:40 by ojessi            #+#    #+#             */
/*   Updated: 2019/06/08 16:09:14 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	zoom(int key, t_map *map)
{
	int		i;
	int		j;
	int		k;
	int		d;

	d = 0;
	k = 0;
	i = -1;
	printf("z befoe = %d\n", map->points[1][1].z);
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			if (key == 32)
			{
				if (j + 1 != map->width && i + 1 != map->height)
				{
					if ((map->points[i][j + 1].x - map->points[i][j].x) >= 500 &&
					(map->points[i + 1][j].y - map->points[i][j].y) >= 500)
						return ;
				}
				map->points[i][j].x *= 2;
				map->points[i][j].y *= 2;
				map->points[i][j].z *= 2;
			}
			else if (key == 2)
			{
				
				if (j + 1 != map->width && i + 1 != map->height)
				{
					if (((map->points[i][j + 1].x - map->points[i][j].x) <= 1) &&
					((map->points[i + 1][j].y - map->points[i][j].y) <= 1))
						return ;
				}
				map->points[i][j].x *= 0.5;
				map->points[i][j].y *= 0.5;
				map->points[i][j].z *= 0.5;
			}
			else if (key == 13)
				map->dz += 1;
			else if (key == 6)
				map->dz -= 1;
		}
	}
	if (key == 13)
		printf("z after up = %d\n", map->points[1][1].z);
	if (key == 6)
		printf("z after down = %d\n", map->points[1][1].z);
	//printf("Количество точек = %d количество нулей = %d\n", d, k);
}

static	int		keyboard(int key, void *param)
{
	t_map	*map;
	int		i;
	int		j;
	static	int	k = 0;
	
	map = param;
	if (key == 53)
		exit(0);
	if (key == 123 || key == 124 || key == 125 || key == 126)
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
	zoom(key, map);
	//ft_putnbr(key);
	mlx_destroy_image(map->mlx_ptr, map->image->img_ptr);
	free(map->image);
	ft_choise_proj(map);
	return (0);
}

void				ft_key_hook(t_map *map)
{
	mlx_hook(map->win_ptr, 2, 0, keyboard, map);
}