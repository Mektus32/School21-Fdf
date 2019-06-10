/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <ojessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 15:54:01 by ojessi            #+#    #+#             */
/*   Updated: 2019/06/10 16:01:48 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_init_map(t_map *map)
{
	map->dx = 1;
	map->dz = 1;
	map->dy = 1;
	map->xmove = 1;
	map->ymove = 1;
	map->proj = 0;
	map->color = 0xE805FF;
	map->d3 = 0;
	map->points3d ? ft_frtwarr((void**)map->points3d, map->height) : 0;
	map->points3d = NULL;
}

void	ft_init_image(t_map *map)
{
	map->image = ft_memalloc(sizeof(t_image));
	map->image->img_data ? free(map->image->img_data) : 0;
	map->image->bpp = 64;
	map->image->endian = 0;
	map->image->size_line = WIN_WIDTH * 4;
}

void	ft_print_menu(t_map *map)
{
	const char *s1 = "COLOR      -> 'C'";
	const char *s2 = "RESTART    -> 'R'";
	const char *s3 = "PROJECTION -> 'P'";
	const char *s4 = "ZOOM       -> + 'U', - 'J'";
	const char *s5 = "RANGE      -> + '+', - '-'";

	mlx_string_put(map->mlx_ptr, map->win_ptr, 100, 100, 0xBAFF05, "MENU");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 25, 125, 0xBAFF05, (char*)s1);
	mlx_string_put(map->mlx_ptr, map->win_ptr, 25, 150, 0xBAFF05, (char*)s2);
	mlx_string_put(map->mlx_ptr, map->win_ptr, 25, 175, 0xBAFF05, (char*)s3);
	mlx_string_put(map->mlx_ptr, map->win_ptr, 25, 200, 0xBAFF05, (char*)s4);
	mlx_string_put(map->mlx_ptr, map->win_ptr, 25, 225, 0xBAFF05, (char*)s5);
	mlx_string_put(map->mlx_ptr, map->win_ptr, 25, 250, 0xBAFF05,
	"LINE       -> start 'LMB', end 'RMB'");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 25, 275, 0xBAFF05,
	"ROTATION_X -> ['1'..'2']");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 25, 300, 0xBAFF05,
	"ROTATION_Y -> ['3'..'4']");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 25, 325, 0xBAFF05,
	"ROTATION_Z -> ['5'..'6']");
}

void	ft_init_3d_and_mouse(t_map *map)
{
	int		i;
	int		j;

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
}

int		main(int argc, char **argv)
{
	t_map	*map;

	if (argc == 2)
	{
		map = ft_memalloc(sizeof(t_map));
		map->file = argv[1];
		ft_parse_points(map, argv[1]);
	}
	else
		write(1, "usage: ./fdf source_file\n", 25);
	return (0);
}
