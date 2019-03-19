/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiven <dpiven@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 17:24:29 by dpiven            #+#    #+#             */
/*   Updated: 2019/03/04 17:24:30 by dpiven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define MENU_OPEN "Press key 0 to open 'MENU'"

static	void	paint_line(t_fdf *fdf, int dx, int dy, int color)
{
	int fault;
	int fault2;

	fault = dx - dy;
	mlx_pixel_put(fdf->init, fdf->win, fdf->cord.x0, fdf->cord.y0, color);
	mlx_pixel_put(fdf->init, fdf->win, fdf->cord.x1, fdf->cord.y1, color);
	while (fdf->cord.x0 != fdf->cord.x1 || fdf->cord.y0 != fdf->cord.y1)
	{
		mlx_pixel_put(fdf->init, fdf->win, fdf->cord.x0, fdf->cord.y0, color);
		fault2 = fault * 2;
		if (fault2 > -dy)
		{
			fault -= dy;
			fdf->cord.x0 += fdf->cord.sign_x;
		}
		if (fault2 < dx)
		{
			fault += dx;
			fdf->cord.y0 += fdf->cord.sign_y;
		}
	}
}

void			paint_map(t_fdf *fdf, int color)
{
	int dx;
	int dy;

	dx = abs(fdf->cord.x1 - fdf->cord.x0);
	dy = abs(fdf->cord.y1 - fdf->cord.y0);
	fdf->cord.sign_x = fdf->cord.x0 < fdf->cord.x1 ? 1 : -1;
	fdf->cord.sign_y = fdf->cord.y0 < fdf->cord.y1 ? 1 : -1;
	paint_line(fdf, dx, dy, color);
}

static	void	h_line(t_fdf *fdf, double x, double y, t_xy xy)
{
	int color;

	color = fdf->map[xy.x][xy.y] && fdf->map[xy.x][xy.y + 1] ?\
		fdf->cord.else_color : fdf->cord.color;
	fdf->cord.x0 = fdf->cord.x_s + (y * fdf->cord.step);
	fdf->cord.y0 = fdf->cord.y_s + (x * fdf->cord.step);
	create_new_cord(fdf, xy.x, xy.y + 1);
	fdf->cord.x1 = fdf->cord.x_s + ((fdf->newcord.y) * fdf->cord.step);
	fdf->cord.y1 = fdf->cord.y_s + (fdf->newcord.x * fdf->cord.step);
	paint_map(fdf, color);
}

static	void	v_line(t_fdf *fdf, double x, double y, t_xy xy)
{
	int color;

	color = fdf->map[xy.x][xy.y] && fdf->map[xy.x + 1][xy.y] ?\
		fdf->cord.else_color : fdf->cord.color;
	fdf->cord.x0 = fdf->cord.x_s + (y * fdf->cord.step);
	fdf->cord.y0 = fdf->cord.y_s + (x * fdf->cord.step);
	create_new_cord(fdf, xy.x + 1, xy.y);
	fdf->cord.x1 = fdf->cord.x_s + (fdf->newcord.y * fdf->cord.step);
	fdf->cord.y1 = fdf->cord.y_s + (fdf->newcord.x * fdf->cord.step);
	paint_map(fdf, color);
}

int				ft_paint_fdf(t_fdf *fdf)
{
	int		x;
	int		y;
	double	xi;
	double	yi;
	t_xy	xy;

	x = -1;
	mlx_string_put(fdf->init, fdf->win, 10, 20, MENU, MENU_OPEN);
	fdf->i == 0 ? initial_values(fdf) : 0;
	while (++x < fdf->h)
	{
		y = -1;
		while (++y < fdf->w)
		{
			create_new_cord(fdf, x, y);
			xi = fdf->newcord.x;
			yi = fdf->newcord.y;
			xy.x = x;
			xy.y = y;
			y < fdf->w - 1 ? h_line(fdf, xi, yi, xy) : 0;
			x < fdf->h - 1 ? v_line(fdf, xi, yi, xy) : 0;
		}
	}
	return (1);
}
