/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiven <dpiven@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 14:54:02 by dpiven            #+#    #+#             */
/*   Updated: 2019/03/19 14:54:03 by dpiven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_init_center(t_fdf *fdf)
{
	fdf->cord.x_s = 2000 / 2;
	fdf->cord.y_s = 1200 / 2;
}

void	calc_step(t_fdf *fdf)
{
	fdf->w < 25 ? fdf->cord.step = 25 : 0;
	fdf->w >= 25 ? fdf->cord.step = 20 : 0;
	fdf->w >= 50 ? fdf->cord.step = 10 : 0;
	fdf->w >= 200 ? fdf->cord.step = 5 : 0;
	fdf->w >= 250 ? fdf->cord.step = 1 : 0;
}

void	ft_proection_slide(t_fdf *fdf)
{
	double proec[3][3];

	proec[0][0] = 0.000796;
	proec[0][1] = 0.000000;
	proec[0][2] = -1.000000;
	proec[1][0] = 0.000000;
	proec[1][1] = 1.000000;
	proec[1][2] = 0.000000;
	proec[2][0] = 1.000000;
	proec[2][1] = 0.000000;
	proec[2][2] = 0.000796;
	ft_free_double_mtrx(fdf->mtrx);
	initial_values(fdf);
	fdf->mtrx = mltp_mtrx(fdf->mtrx, proec, fdf);
}

void	ft_proection(t_fdf *fdf)
{
	double proec[3][3];

	proec[0][0] = 0.411053;
	proec[0][1] = -0.320947;
	proec[0][2] = -0.853246;
	proec[1][0] = 0.756350;
	proec[1][1] = 0.642562;
	proec[1][2] = 0.122674;
	proec[2][0] = 0.508892;
	proec[2][1] = -0.695778;
	proec[2][2] = 0.506875;
	ft_free_double_mtrx(fdf->mtrx);
	initial_values(fdf);
	fdf->mtrx = mltp_mtrx(fdf->mtrx, proec, fdf);
}
