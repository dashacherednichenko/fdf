/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiven <dpiven@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 11:11:34 by dpiven            #+#    #+#             */
/*   Updated: 2019/03/19 11:11:35 by dpiven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double			**mltp_mtrx(double **a, double b[3][3], t_fdf *fdf)
{
	int		i;
	double	**c;

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
	ft_free_double_mtrx(fdf->mtrx);
	return (c);
}

double			**ft_rotate_x(t_fdf *fdf, int sign, double angle)
{
	double **newmtrx;
	double rotate_x[3][3];

	rotate_x[0][0] = 1;
	rotate_x[0][1] = 0;
	rotate_x[0][2] = 0;
	rotate_x[1][0] = 0;
	rotate_x[1][1] = cos(sign * angle);
	rotate_x[1][2] = -sin(sign * angle);
	rotate_x[2][0] = 0;
	rotate_x[2][1] = sin(sign * angle);
	rotate_x[2][2] = cos(sign * angle);
	newmtrx = mltp_mtrx(fdf->mtrx, rotate_x, fdf);
	return (newmtrx);
}

double			**ft_rotate_y(t_fdf *fdf, int sign, double angle)
{
	double **newmtrx;
	double rotate_y[3][3];

	rotate_y[0][0] = cos(sign * angle);
	rotate_y[0][1] = 0;
	rotate_y[0][2] = sin(sign * angle);
	rotate_y[1][0] = 0;
	rotate_y[1][1] = 1;
	rotate_y[1][2] = 0;
	rotate_y[2][0] = -sin(sign * angle);
	rotate_y[2][1] = 0;
	rotate_y[2][2] = cos(sign * angle);
	newmtrx = mltp_mtrx(fdf->mtrx, rotate_y, fdf);
	return (newmtrx);
}

double			**ft_rotate_z(t_fdf *fdf, int sign, double angle)
{
	double **newmtrx;
	double rotate_z[3][3];

	rotate_z[0][0] = cos(sign * angle);
	rotate_z[0][1] = -sin(sign * angle);
	rotate_z[0][2] = 0;
	rotate_z[1][0] = sin(sign * angle);
	rotate_z[1][1] = cos(sign * angle);
	rotate_z[1][2] = 0;
	rotate_z[2][0] = 0;
	rotate_z[2][1] = 0;
	rotate_z[2][2] = 1;
	newmtrx = mltp_mtrx(fdf->mtrx, rotate_z, fdf);
	return (newmtrx);
}
