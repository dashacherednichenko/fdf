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

static	void	h_v_line(t_fdf *fdf, int x, int y, int i)
{
	fdf->cord.x0 = fdf->cord.x_s + (y * fdf->cord.step);// - \
		(x * fdf->cord.angle) + (x * fdf->cord.angle_y);
	fdf->cord.y0 = fdf->cord.y_s + (x * fdf->cord.step);// - fdf->map[x][y];// \
		* fdf->cord.po_z - (y * fdf->cord.angle_z) - (y * fdf->p.angle_y);
		i == 1 ? y++ : x++;
	fdf->cord.x1 = fdf->cord.x_s + (y * fdf->cord.step);// - \
		(x * fdf->cord.angle) + (x * fdf->p.angle_y);
	fdf->cord.y1 = fdf->cord.y_s + (x * fdf->cord.step);// - \
		fdf->map[x][y + 1] * fdf->cord.po_z - ((y + 1) \
		* fdf->cord.angle_z) - ((y + 1) * fdf->cord.angle_y);
//	two_colors(fdf, x, y, fdf->map.values[x][y]);
	paint_map(fdf);
}

//static	void	v_line(t_fdf *fdf, int x, int y)
//{
//	fdf->cord.x0 = fdf->cord.x_s + (y * fdf->cord.step);// - \
//		(i * fdf->cord.angle) + (i * fdf->cord.angle_y);
//	fdf->cord.y0 = fdf->cord.y_s + (x * fdf->cord.step);// - \
//		fdf->map[i][j] * fdf->cord.po_z - ((j) * \
//		fdf->cord.angle_z) - (j * fdf->cord.angle_y);
//	fdf->cord.x1 = fdf->cord.x_s + (y * fdf->cord.step);// - ((i + 1) * \
//		fdf->p.angle) + ((i + 1) * fdf->cord.angle_y);
//	fdf->cord.y1 = fdf->cord.y_s + ((x + 1) * fdf->cord.step);// - \
//		fdf->map[i + 1][j] * fdf->cord.po_z - \
//		(j * fdf->cord.angle_z) - (j * fdf->cord.angle_y);
////	two_colors(fdf, i, j, fdf->map.values[i][j]);
//	paint_map(fdf);
//}


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
				h_v_line(fdf, x, y, 1);
			if (x < fdf->h)
				h_v_line(fdf, x, y, 0);
			y++;
		}
		x++;
	}
	return (1);
}

