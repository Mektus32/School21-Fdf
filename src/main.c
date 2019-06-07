/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <ojessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 15:54:01 by ojessi            #+#    #+#             */
/*   Updated: 2019/06/07 21:01:28 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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