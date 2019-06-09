/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_coor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <ojessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 20:25:11 by ojessi            #+#    #+#             */
/*   Updated: 2019/06/09 20:59:29 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	iso(double *x, double *y, double z)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (int)((previous_x - previous_y) * cos(0.523599));
	*y = (int)(-z + (previous_x + previous_y) * sin(0.523599));
}

void	x_rotation(double x, double *y, double *z, t_map *map)
{
	int			tmpx;
	double		tmpy;
	double		tmpz;

	tmpx = x;
	tmpy = *y;
	tmpz = *z;
	x = tmpx;
	*y = (double)tmpy * cos(map->mouse->angel) + (double)tmpz *
	sin(map->mouse->angel);
	*z = (double)-tmpy * sin(map->mouse->angel) + (double)tmpz *
	cos(map->mouse->angel);
}

void	y_rotation(double *x, double y, double *z, t_map *map)
{
	double		tmpx;
	int			tmpy;
	double		tmpz;

	tmpx = *x;
	tmpy = y;
	tmpz = *z;
	*x = (double)tmpx * cos(map->mouse->angel) + (double)tmpz *
	sin(map->mouse->angel);
	y = tmpy;
	*z = (double)-tmpx * sin(map->mouse->angel) + (double)tmpz *
	cos(map->mouse->angel);
}

void	z_rotation(double *x, double *y, double z, t_map *map)
{
	double		tmpx;
	double		tmpy;
	int			tmpz;

	tmpx = *x;
	tmpy = *y;
	tmpz = z;
	*x = (double)tmpx * cos(map->mouse->angel) - (double)tmpy *
	sin(map->mouse->angel);
	*y = (double)tmpx * sin(map->mouse->angel) + (double)tmpy *
	cos(map->mouse->angel);
	z = tmpy;
}
