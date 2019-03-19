/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiven <dpiven@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 11:58:37 by dpiven            #+#    #+#             */
/*   Updated: 2019/03/19 11:58:55 by dpiven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_proection(t_fdf *fdf)
{
	double proec[3][3];

	proec[0][0] = 0.411053 ;
	proec[0][1] = -0.320947;
	proec[0][2] = -0.853246 ;
	proec[1][0] = 0.756350;
	proec[1][1] = 0.642562;
	proec[1][2] = 0.122674;
	proec[2][0] = 0.508892;
	proec[2][1] = -0.695778;
	proec[2][2] = 0.506875;

	ft_free_double_mtrx(fdf->mtrx);
	initial_values(fdf);
//	system("leaks -q fdf");
	fdf->mtrx = mltp_mtrx(fdf->mtrx, proec, fdf);
//	system("leaks -q fdf");
///	fdf->mtrx = ft_rotate_y(fdf, 1, 0.523599);
//	/їsystem("leaks -q fdf");
//	fdf->mtrx = ft_rotate_z(fdf, 1, 0.523599);
//	system("leaks -q fdf");
}

int		deal_key(int key, t_fdf *fdf)
{
	mlx_clear_window(fdf->init, fdf->win);
	key == 82 || key == 29 ? show_menu(fdf) : 0;
	key == 53 ? exit_fdf() : 0;
	if (key == 36)
	{
		ft_free_double_mtrx(fdf->mtrx);
		initial_values(fdf);
	}
	key == 35 ? ft_proection(fdf) : 0;
	if (key == 69 && fdf->cord.step <= 100)
	{
		fdf->cord.step += 1;
		ft_init_center(fdf);
	}
	if (key == 78 && fdf->cord.step >= 5)
	{
		fdf->cord.step -= 1;
		ft_init_center(fdf);
	}
	key == 124 ? fdf->mtrx = ft_rotate_x(fdf, 1, 2 * 3.14 / 180) : 0;
	ft_printmtrx33(fdf->mtrx);
	key == 123 ? fdf->mtrx = ft_rotate_x(fdf, -1, 2 * 3.14 / 180) : 0;
	key == 125 ? fdf->mtrx = ft_rotate_y(fdf, 1, 2 * 3.14 / 180) : 0;
	key == 126 ? fdf->mtrx = ft_rotate_y(fdf, -1, 2 * 3.14 / 180) : 0;
	key == 6 ? fdf->mtrx = ft_rotate_z(fdf, 1, 2 * 3.14 / 180) : 0;
	key == 7 ? fdf->mtrx = ft_rotate_z(fdf, -1, 2 * 3.14 / 180) : 0;
	key == 13 && fdf->cord.z_s <= 40 ? fdf->cord.z_s += 1 : 0;
	key == 1 && fdf->cord.z_s >= -40 ? fdf->cord.z_s -= 1 : 0;
	key == 8 ? ft_change_color(fdf) : 0;
	(key == 18 || key == 83) && fdf->cord.x_s >= 1 ? fdf->cord.x_s -= 10 : 0;
	(key == 23 || key == 87) && fdf->cord.y_s >= 1 ? fdf->cord.y_s -= 10 : 0;
	(key == 19 || key == 84) && fdf->cord.y_s <= 1100 ? fdf->cord.y_s += 10 : 0;
	(key == 20 || key == 85) && fdf->cord.x_s <= 1900 ? fdf->cord.x_s += 10 : 0;
//	ft_init_center(fdf);
	ft_paint_fdf(fdf);

//	system("leaks -q fdf");
	return (0);
}

void	show_menu(t_fdf *fdf)
{
	mlx_string_put(fdf->init, fdf->win, 1450, 960, MENU,
			"reset               :            ENTER");
	mlx_string_put(fdf->init, fdf->win, 1450, 980, MENU,
			"proection isometric :                P");
	mlx_string_put(fdf->init, fdf->win, 1450, 1000, MENU,
			"rotation X          :arrow right, left");
	mlx_string_put(fdf->init, fdf->win, 1450, 1020, MENU,
			"rotation Y          :   arrow up, down");
	mlx_string_put(fdf->init, fdf->win, 1450, 1040, MENU,
			"rotation Z          :             Z, X");
	mlx_string_put(fdf->init, fdf->win, 1450, 1060, MENU,
			"to move map         :       1, 2, 3, 5");
	mlx_string_put(fdf->init, fdf->win, 1450, 1080, MENU,
			"to change color     :                C");
	mlx_string_put(fdf->init, fdf->win, 1450, 1100, MENU,
			"grow up/grow down   :              W/S");
	mlx_string_put(fdf->init, fdf->win, 1450, 1120, MENU,
			"zoom ++             :                +");
	mlx_string_put(fdf->init, fdf->win, 1450, 1140, MENU,
			"zoom --             :                -");
	mlx_string_put(fdf->init, fdf->win, 1450, 1160, MENU,
			"exit or close window:              ESC");
}

void	create_new_cord(t_fdf *fdf, int x, int y)
{
	int xi;
	int yi;

	xi = x;
	yi = y;
	x = x * (500/(500));
	y = y * (500/(500));
	fdf->newcord.x = fdf->mtrx[0][0] * (x -  fdf->w / 2);
	fdf->newcord.x += fdf->mtrx[0][1] * (y -  fdf->h / 2);
	fdf->newcord.x += fdf->mtrx[0][2] * fdf->map[xi][yi] * fdf->cord.z_s;
	fdf->newcord.y = fdf->mtrx[1][0] * (x -  fdf->w / 2);
	fdf->newcord.y += fdf->mtrx[1][1] * (y -  fdf->h / 2);
	fdf->newcord.y += fdf->mtrx[1][2] * fdf->map[xi][yi] * fdf->cord.z_s;
//	fdf->newcord.x = fdf->newcord.x * (500/(500+fdf->map[x][y]));
//	fdf->newcord.y = fdf->newcord.y * (500/(500+fdf->map[x][y]));
}

void	initial_values(t_fdf *fdf)
{
	fdf->mtrx = create_bz_mtrx(0);
	fdf->cord.step = 20;
	fdf->cord.x_s = 2000 / 2;
	fdf->cord.y_s = 1200 / 2;
	fdf->cord.z_s = 1;
	fdf->cord.i = 0;
	fdf->cord.color = 16777215;
	fdf->cord.else_color = 15865546;
	fdf->i = 1;
}
