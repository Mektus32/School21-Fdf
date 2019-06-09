/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_points.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <ojessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 16:03:14 by ojessi            #+#    #+#             */
/*   Updated: 2019/06/09 19:50:54 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define PTR map->mlx_ptr

void			ft_choise_proj(t_map *map)
{
	int		i;
	int		j;
	t_line	*line;

	map->image->img_ptr = mlx_new_image(map->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
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
				map->d3 == 1 ? ft_horiz_line_3d(i, j, line, map) :
				ft_horiz_line(i, j, line, map);
			if (j <= map->width && i < map->height - 1)
				map->d3 == 1 ? ft_vertic_line_3d(i, j, line, map) :
				ft_vertic_line(i, j, line, map);
			free(line);
		}
	}
	mlx_put_image_to_window(PTR, map->win_ptr, map->image->img_ptr, 0, 0);
	ft_print_menu(map);
}

static	void	ft_create_window(t_map *map)
{
	if (map->mlx_ptr == NULL)
	{
		map->mlx_ptr = mlx_init();
		map->win_ptr = mlx_new_window(map->mlx_ptr, WIN_WIDTH,
		WIN_HEIGHT, "FDF");
	}
	if (map->image == NULL)
		ft_init_image(map);
	ft_init_map(map);
	ft_key_hook(map);
	ft_choise_proj(map);
	mlx_loop(map->mlx_ptr);
}

static	void	ft_push_coor(t_map *map, char *file)
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
			map->points[i][j].x = (j - map->width / 2) * 10;
			map->points[i][j].y = (i - map->height / 2) * 10;
			map->points[i][j].z = ft_atoi(tmp[j]) * 10;
		}
		i++;
		ft_frtwarr((void**)tmp, map->height);
		free(line);
	}
	ft_create_window(map);
}

static	void	ft_valid_line(char *line, int check, t_map *map)
{
	int		i;

	i = -1;
	while (line[++i] != '\0')
		if (!ft_isspace(line[i]) && !ft_isdigit(line[i]) && line[i] != '-')
		{
			write(1, "invalid file\n", 13);
			exit(-1);
		}
	if (check != map->width && map->height != 0)
	{
		write(1, "invalid file\n", 13);
		exit(-1);
	}
}

void			ft_parse_points(t_map *map, char *file)
{
	int		fd;
	char	*line;
	int		i;
	int		check;

	if ((fd = open(file, O_RDONLY)) < 0)
		return ;
	map->height = 0;
	map->width = 0;
	while (get_next_line(fd, &line) > 0)
	{
		check = map->width;
		map->width = ft_count_words(line);
		ft_valid_line(line, check, map);
		map->height++;
		free(line);
	}
	map->points = (t_point**)malloc(sizeof(t_point*) * map->height);
	i = -1;
	while (++i < map->height)
		map->points[i] = (t_point*)malloc(sizeof(t_point) * map->width);
	close(fd);
	ft_push_coor(map, file);
}
