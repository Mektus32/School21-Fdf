/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <ojessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 16:56:52 by ojessi            #+#    #+#             */
/*   Updated: 2019/06/09 20:25:00 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			ft_horiz_line(int i, int j, t_line *line, t_map *map)
{
	line->start.x = (map->points[i][j].x * map->dx + map->xmove);
	line->start.y = (map->points[i][j].y * map->dy + map->ymove);
	line->stop.x = (map->points[i][j + 1].x * map->dx + map->xmove);
	line->stop.y = (map->points[i][j + 1].y * map->dy + map->ymove);
	if (map->proj == 1)
	{
		iso(&line->start.x, &line->start.y, map->points[i][j].z * map->dz / 4);
		iso(&line->stop.x, &line->stop.y, map->points[i][j + 1].z
		* map->dz / 4);
	}
	ft_print_line(map, line);
}

void			ft_vertic_line(int i, int j, t_line *line, t_map *map)
{
	line->start.x = (map->points[i][j].x * map->dx + map->xmove);
	line->start.y = (map->points[i][j].y * map->dy + map->ymove);
	line->stop.x = (map->points[i + 1][j].x * map->dx + map->xmove);
	line->stop.y = (map->points[i + 1][j].y * map->dy + map->ymove);
	if (map->proj == 1)
	{
		iso(&line->start.x, &line->start.y, map->points[i][j].z * map->dz / 4);
		iso(&line->stop.x, &line->stop.y, map->points[i + 1][j].z *
		map->dz / 4);
	}
	ft_print_line(map, line);
}

void			ft_horiz_line_3d(int i, int j, t_line *line, t_map *map)
{
	if (map->points3d != NULL)
	{
		line->start.x = (map->points3d[i][j].x * map->dx + map->xmove);
		line->start.y = (map->points3d[i][j].y * map->dy + map->ymove);
		line->stop.x = (map->points3d[i][j + 1].x * map->dx + map->xmove);
		line->stop.y = (map->points3d[i][j + 1].y * map->dy + map->ymove);
		if (map->proj == 1)
		{
			iso(&line->start.x, &line->start.y, map->points3d[i][j].z *
			map->dz / 8);
			iso(&line->stop.x, &line->stop.y, map->points3d[i][j + 1].z *
			map->dz / 8);
		}
		ft_print_line(map, line);
	}
}

void			ft_vertic_line_3d(int i, int j, t_line *line, t_map *map)
{
	if (map->points3d != NULL)
	{
		line->start.x = (map->points3d[i][j].x * map->dx + map->xmove);
		line->start.y = (map->points3d[i][j].y * map->dy + map->ymove);
		line->stop.x = (map->points3d[i + 1][j].x * map->dx + map->xmove);
		line->stop.y = (map->points3d[i + 1][j].y * map->dy + map->ymove);
		if (map->proj == 1)
		{
			iso(&line->start.x, &line->start.y, map->points3d[i][j].z *
			map->dz / 8);
			iso(&line->stop.x, &line->stop.y, map->points3d[i + 1][j].z *
			map->dz / 8);
		}
		ft_print_line(map, line);
	}
}
