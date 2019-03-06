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

static	void	paint_line(t_fdf *fdf, int dx, int dy)
{
	int fault;
	int fault2;

	fault = dx - dy;
	mlx_pixel_put(fdf->init, fdf->win, fdf->cord.x1, fdf->cord.y1, fdf->cord.color);
	while (fdf->cord.x0 != fdf->cord.x1 || fdf->cord.y0 != fdf->cord.y1)
	{
		mlx_pixel_put(fdf->init, fdf->win, fdf->cord.x0, fdf->cord.y0, fdf->cord.color);
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

void			paint_map(t_fdf *fdf)
{
	int dx;
	int dy;

	dx = abs(fdf->cord.x1 - fdf->cord.x0);
	dy = abs(fdf->cord.y1 - fdf->cord.y0);
	fdf->cord.sign_x = fdf->cord.x0 < fdf->cord.x1 ? 1 : -1;
	fdf->cord.sign_y = fdf->cord.y0 < fdf->cord.y1 ? 1 : -1;
	paint_line(fdf, dx, dy);
}

static	void	h_line(t_fdf *fdf, int x, int y)
{
	fdf->cord.x0 = fdf->cord.x_s + (y * fdf->cord.step);
	fdf->cord.y0 = fdf->cord.y_s + (x * fdf->cord.step) - fdf->map[x][y] * fdf->cord.z_s;
	fdf->cord.x1 = fdf->cord.x_s + ((y + 1) * fdf->cord.step);
	fdf->cord.y1 = fdf->cord.y_s + (x * fdf->cord.step) - fdf->map[x][y + 1] * fdf->cord.z_s;
	paint_map(fdf);
}

static	void	v_line(t_fdf *fdf, int x, int y)
{
	fdf->cord.x0 = fdf->cord.x_s + (y * fdf->cord.step);
	fdf->cord.y0 = fdf->cord.y_s + (x * fdf->cord.step) - fdf->map[x][y] * fdf->cord.z_s;
	fdf->cord.x1 = fdf->cord.x_s + (y * fdf->cord.step);
	fdf->cord.y1 = fdf->cord.y_s + ((x + 1) * fdf->cord.step) - fdf->map[x + 1][y] * fdf->cord.z_s;
	paint_map(fdf);
}


void		initial_values(t_fdf *fdf)
{
	fdf->cord.x_s = 450;
	fdf->cord.y_s = 250;
	fdf->cord.step = 10;
	fdf->cord.z_s = 0;
	fdf->cord.i = 0;
	fdf->cord.color = 16777215;
	fdf->i = 1;
}

int	ft_paint_fdf(t_fdf *fdf)
{
	int x;
	int y;

	x = 0;
	mlx_string_put(fdf->init, fdf->win, 10, 20, MENU, "Press key 0 to open 'MENU'");
	if (fdf->i == 0)
		initial_values(fdf);
	while (x < fdf->h)
	{
		y = 0;
		while (y < fdf->w)
		{
			if (y < fdf->w - 1)
				h_line(fdf, x, y);
			if (x < fdf->h - 1)
				v_line(fdf, x, y);
			y++;
		}
		x++;
	}
	return (1);
}

