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

void ft_free_double_mtrx(double **a)
{
	int x;

	x = 0;
	while (x < 3)
	{
		free (a[x++]);
	}
	free (a);
}

double 	**mltp_mtrx (double **a, double b[3][3])
{
	int i;
	double **c;

i = 0;
	c = (double**)malloc(sizeof(double*) * 3);
	while (i < 3)
		c[i++] = (double*)malloc(sizeof(double) * 3);
	c[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0] + a[0][2] * b[2][0];
	c[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1] + a[0][2] * b[2][1];
	c[0][2] = a[0][0] * b[0][2] + a[0][1] * b[1][2] + a[0][2] * b[2][2];
	c[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0] + a[1][2] * b[2][0];
	c[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1] + a[1][2] * b[2][1];
	c[1][2] = a[1][0] * b[0][2] + a[1][1] * b[1][2] + a[1][2] * b[2][2];
	c[2][0] = a[2][0] * b[0][0] + a[2][1] * b[1][0] + a[2][2] * b[2][0];
	c[2][1] = a[2][0] * b[0][1] + a[2][1] * b[1][1] + a[2][2] * b[2][1];
	c[2][2] = a[2][0] * b[0][2] + a[2][1] * b[1][2] + a[2][2] * b[2][2];
//	ft_free_double_mtrx(fdf->mtrx);
	return (c);
}

double	**ft_rotate_x(t_fdf *fdf, int sign)
{
	double **newmtrx;
	double rotate_x[3][3];
	double angle;

	angle = 2 * 3.14 / 180;

	rotate_x[0][0] = 1;
	rotate_x[0][1] = 0;
	rotate_x[0][2] = 0;
	rotate_x[1][0] = 0;
	rotate_x[1][1] = cos(sign * angle);
	rotate_x[1][2] = -sin(sign * angle);
	rotate_x[2][0] = 0;
	rotate_x[2][1] = sin(sign * angle);
	rotate_x[2][2] = cos(sign * angle);
	newmtrx = mltp_mtrx(fdf->mtrx, rotate_x);
	return (newmtrx);
}

double	**ft_rotate_y(t_fdf *fdf, int sign)
{
	double **newmtrx;
	double rotate_y[3][3];
	double angle;

	angle = 2 * 3.14 / 180;

	rotate_y[0][0] = cos(sign * angle);
	rotate_y[0][1] = 0;
	rotate_y[0][2] = sin(sign * angle);
	rotate_y[1][0] = 0;
	rotate_y[1][1] = 1;
	rotate_y[1][2] = 0;
	rotate_y[2][0] = -sin(sign * angle);
	rotate_y[2][1] = 0;
	rotate_y[2][2] = cos(sign * angle);
	newmtrx = mltp_mtrx(fdf->mtrx, rotate_y);
	return (newmtrx);
}

double	**ft_rotate_z(t_fdf *fdf, int sign)
{
	double **newmtrx;
	double rotate_z[3][3];
	double angle;

	angle = 2 * 3.14 / 180;
	rotate_z[0][0] = cos(sign * angle);
	rotate_z[0][1] = -sin(sign * angle);
	rotate_z[0][2] = 0;
	rotate_z[1][0] = sin(sign * angle);
	rotate_z[1][1] = cos(sign * angle);
	rotate_z[1][2] = 0;
	rotate_z[2][0] = 0;
	rotate_z[2][1] = 0;
	rotate_z[2][2] = 1;
	newmtrx = mltp_mtrx(fdf->mtrx, rotate_z);
	return (newmtrx);
}


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

static	void	h_line(t_fdf *fdf, double x, double y, int xi, int yi)
{
	int color;

	color = fdf->map[xi][yi] && fdf->map[xi][yi + 1] ? fdf->cord.else_color : fdf->cord.color;
	fdf->cord.x0 = fdf->cord.x_s + (y * fdf->cord.step);
	fdf->cord.y0 = fdf->cord.y_s + (x * fdf->cord.step);
	create_new_cord(fdf, xi, yi + 1);
	fdf->cord.x1 = fdf->cord.x_s + ((fdf->newcord.y) * fdf->cord.step);
	fdf->cord.y1 = fdf->cord.y_s + (fdf->newcord.x * fdf->cord.step);
	paint_map(fdf, color);
}

static	void	v_line(t_fdf *fdf, double x, double y, int xi, int yi)
{
	int color;

	color = fdf->map[xi][yi] && fdf->map[xi + 1][yi] ? fdf->cord.else_color : fdf->cord.color;
	fdf->cord.x0 = fdf->cord.x_s + (y * fdf->cord.step);
	fdf->cord.y0 = fdf->cord.y_s + (x * fdf->cord.step);
	create_new_cord(fdf, xi + 1, yi);
	fdf->cord.x1 = fdf->cord.x_s + (fdf->newcord.y * fdf->cord.step);
	fdf->cord.y1 = fdf->cord.y_s + (fdf->newcord.x * fdf->cord.step);
	paint_map(fdf, color);
}


void		initial_values(t_fdf *fdf)
{
	fdf->mtrx = create_bz_mtrx(0);
	fdf->cord.x_s = 450;
	fdf->cord.y_s = 250;
	fdf->cord.step = 10;
	fdf->cord.z_s = 1;
	fdf->cord.i = 0;
	fdf->cord.color = 16777215;
	fdf->cord.else_color = 15865546;
	fdf->i = 1;
}

void	create_new_cord(t_fdf *fdf, int x,int y)
{
	fdf->newcord.x = fdf->mtrx[0][0] * x;
	fdf->newcord.x += fdf->mtrx[0][1] * y;
	fdf->newcord.x += fdf->mtrx[0][2] * fdf->map[x][y] * fdf->cord.z_s;
	fdf->newcord.y = fdf->mtrx[1][0] * x;
	fdf->newcord.y += fdf->mtrx[1][1] * y;
	fdf->newcord.y += fdf->mtrx[1][2] * fdf->map[x][y] * fdf->cord.z_s;
}

int	ft_paint_fdf(t_fdf *fdf)
{
	int x;
	int y;
	double xi;
	double yi;

	x = 0;
	mlx_string_put(fdf->init, fdf->win, 10, 20, MENU, "Press key 0 to open 'MENU'");
	if (fdf->i == 0)
		initial_values(fdf);
	while (x < fdf->h)
	{
		y = 0;
		while (y < fdf->w)
		{
			create_new_cord(fdf, x, y);
			xi = fdf->newcord.x;
			yi = fdf->newcord.y;
			if (y < fdf->w - 1)
				h_line(fdf, xi, yi, x, y);
			if (x < fdf->h - 1)
				v_line(fdf, xi, yi, x, y);
			y++;
		}
		x++;
	}
	return (1);
}

