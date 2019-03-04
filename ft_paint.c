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

	fault = dy <= dx ? -dx : -dy;

	while (fdf->cord.x0 != fdf->cord.x1 || fdf->cord.y0 != fdf->cord.y1)
	{
		mlx_pixel_put(fdf->init, fdf->win, \
				fdf->cord.x0, fdf->cord.y0, fdf->cord.color);
		if (dy <= dx)
			fdf->cord.x0 += fdf->cord.sign_x;
		else
			fdf->cord.y0 += fdf->cord.sign_y;
		fault = dy <= dx ? fault + 2 * dy : fault + 2 * dx;
		if (fault > 0)
		{
			fault = dy <= dx ? fault - 2 * dx : fault - 2 * dy;
			if (dx <= dy)
				fdf->cord.y0 += fdf->cord.sign_y;
			else
				fdf->cord.x0 += fdf->cord.sign_x;
		}
	}
}

void			paint_map(t_fdf *fdf)
{
	int dx;
	int dy;

	dx = fabs(fdf->cord.x1 - fdf->cord.x0);
	dy = fabs(fdf->cord.y1 - fdf->cord.y0);
	fdf->cord.sign_x = fdf->cord.x1 >= fdf->cord.x0 ? 1 : -1;
	fdf->cord.sign_y = fdf->cord.y1 >= fdf->cord.y0 ? 1 : -1;
	mlx_pixel_put(fdf->init, fdf->win, \
			fdf->cord.x0, fdf->cord.y0, fdf->cord.color);
//	fdf->cord.fast_l = (dy <= dx) ? 'x' : 'y';
	paint_line(fdf, dx, dy);
}

static	void	paint_h_line(t_fdf *fdf, int i, int j)
{
	fdf->cord.x0 = fdf->cord.x_s + (j * fdf->cord.step);// - \
		(i * fdf->cord.angle) + (i * fdf->cord.angle_y);
	fdf->cord.y0 = fdf->cord.y_s + (i * fdf->cord.step);// - fdf->map[i][j];// \
		* fdf->cord.po_z - (j * fdf->cord.angle_z) - (j * fdf->p.angle_y);
	fdf->cord.x1 = fdf->cord.x_s + ((j + 1) * fdf->cord.step);// - \
		(i * fdf->cord.angle) + (i * fdf->p.angle_y);
	fdf->cord.y1 = fdf->cord.y_s + (i * fdf->cord.step);// - \
		fdf->map[i][j + 1] * fdf->cord.po_z - ((j + 1) \
		* fdf->cord.angle_z) - ((j + 1) * fdf->cord.angle_y);
//	two_colors(fdf, i, j, fdf->map.values[i][j]);
	paint_map(fdf);
}

static	void	paint_v_line(t_fdf *fdf, int i, int j)
{
	fdf->cord.x0 = fdf->cord.x_s + (j * fdf->cord.step);// - \
		(i * fdf->cord.angle) + (i * fdf->cord.angle_y);
	fdf->cord.y0 = fdf->cord.y_s + (i * fdf->cord.step);// - \
		fdf->map[i][j] * fdf->cord.po_z - ((j) * \
		fdf->cord.angle_z) - (j * fdf->cord.angle_y);
	fdf->cord.x1 = fdf->cord.x_s + (j * fdf->cord.step);// - ((i + 1) * \
		fdf->p.angle) + ((i + 1) * fdf->cord.angle_y);
	fdf->cord.y1 = fdf->cord.y_s + ((i + 1) * fdf->cord.step);// - \
		fdf->map[i + 1][j] * fdf->cord.po_z - \
		(j * fdf->cord.angle_z) - (j * fdf->cord.angle_y);
//	two_colors(fdf, i, j, fdf->map.values[i][j]);
	paint_map(fdf);
}


void		initial_values(t_fdf *fdf)
{
	fdf->cord.x_s = 450;
	fdf->cord.y_s = 250;
	fdf->cord.step = 25;
}

int	ft_paint_fdf(t_fdf *fdf)
{
	int x;
	int y;

	x = 0;
	initial_values(fdf);
	fdf->cord.color = 13172735;
//	mlx_string_put(fdf->init, fdf->win, 300, 10, 5822086, "Press key 0");
	while (x <= fdf->h)
	{
		y = 0;
		while (y <= fdf->w)
		{
			if (y < fdf->w)
				paint_h_line(fdf, x, y);
			if (x < fdf->h)
				paint_v_line(fdf, x, y);
			y++;
		}
		x++;
	}
	return (1);
}

