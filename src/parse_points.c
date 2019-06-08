/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_points.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <ojessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 16:03:14 by ojessi            #+#    #+#             */
/*   Updated: 2019/06/08 16:14:27 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void iso(int *x, int *y, int z)
{
    int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = (previous_x - previous_y) * cos(0.523599);
    *y = -z  + (previous_x + previous_y) * sin(0.523599);
}

void		ft_choise_proj(t_map *map)
{
	int		i;
	int		j;
	t_line *line;

	map->image = ft_memalloc(sizeof(t_image));
	map->image->img_ptr = mlx_new_image(map->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	map->image->bpp = 64;
	map->image->endian = 0;
	map->image->size_line = WIN_WIDTH * 4;	
	map->image->img_data = mlx_get_data_addr(map->image->img_ptr,
	&map->image->bpp, &map->image->size_line, &map->image->endian);
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			line = ft_memalloc(sizeof(t_line));
			if (i <= map->height && j < map->width - 1)
			{
				line->start.x = map->points[i][j].x;
				line->start.y = map->points[i][j].y;
				line->stop.x = map->points[i][j + 1].x;
				line->stop.y = map->points[i][j + 1].y;
				if (map->proj == 1)
				{
					iso(&line->start.x, &line->start.y, map->points[i][j].z * map->dz);
					iso(&line->stop.x, &line->stop.y , map->points[i][j + 1].z * map->dz);
				}
				ft_print_line(map, line);

			}
			if (j <= map->width && i < map->height - 1)
			{
				line->start.x = map->points[i][j].x;
				line->start.y = map->points[i][j].y;
				line->stop.x = map->points[i + 1][j].x;
				line->stop.y = map->points[i + 1][j].y;
				if (map->proj == 1)
				{
					iso(&line->start.x, &line->start.y, map->points[i][j].z * map->dz);
					iso(&line->stop.x, &line->stop.y, map->points[i + 1][j].z * map->dz);
				}
				ft_print_line(map ,line);
			}
			free(line);
		}
	}
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->image->img_ptr, 0, 0);
}

static	void	ft_create_window(t_map *map)
{
	if (map->mlx_ptr == NULL)
	{
		map->mlx_ptr = mlx_init();
		map->win_ptr = mlx_new_window(map->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");
	}
	map->dz = 1;
	map->proj = 0;
	map->color = 0xE805FF;
	ft_key_hook(map);
	ft_choise_proj(map);
	mlx_loop(map->mlx_ptr);
}

void	ft_push_coor(t_map *map, char *file)
{
	int		fd;
	char	*line;
	int		i;
	int		j;
	char	**tmp;

	if ((fd = open(file, O_RDONLY)) < 0)
		return ;
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		tmp = ft_strsplit(line, ' ');
		j = -1;
		while (++j < map->width)
		{
			map->points[i][j].x = j * ZOOM;
			map->points[i][j].y = i * ZOOM;
			map->points[i][j].z = ft_atoi(tmp[j]) * ZOOM / 2;
		}
		i++;
		ft_frtwarr((void**)tmp, map->height);
		free(line);
	}
	ft_create_window(map);
}

void			ft_parse_points(t_map *map, char *file)
{
	int		fd;
	char	*line;
	int		i;

	if ((fd = open(file, O_RDONLY)) < 0)
		return ;
	map->height = 0;
	while (get_next_line(fd, &line) > 0)
	{
		map->height++ == 0 ? map->width = ft_count_words(line) : 0;
		free(line);
	}
	map->points = (t_point**)malloc(sizeof(t_point*) * map->height);
	i = -1;
	while (++i < map->height)
		map->points[i] = (t_point*)malloc(sizeof(t_point) * map->width);
	close(fd);
	ft_push_coor(map, file);
}