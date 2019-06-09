/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <ojessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 15:54:01 by ojessi            #+#    #+#             */
/*   Updated: 2019/06/09 18:45:55 by ojessi           ###   ########.fr       */
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