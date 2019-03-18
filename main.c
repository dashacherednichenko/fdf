/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiven <dpiven@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:55:01 by dpiven            #+#    #+#             */
/*   Updated: 2019/02/27 15:55:03 by dpiven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		exit_fdf(void)
{
	system("leaks -q fdf > leaks.txt");
	exit(0);
}


void	show_menu(t_fdf *fdf)
{

//	mlx_string_put(fdf->init, fdf->win, 1450, 1040, MENU,
//				   "zoom and rotation: arrows up, down, left and right");
//	mlx_string_put(fdf->init, fdf->win, 1450, 1060, MENU,
//				   "projection:        SPACE");
//	mlx_string_put(fdf->init, fdf->win, 1450, 1080, MENU,
//				   "some interesting:  O");
//	mlx_string_put(fdf->init, fdf->win, 1450, 1100, MENU,
//				   "two colors:        L");
//	mlx_string_put(fdf->init, fdf->win, 1450, 1140, MENU,
//				   "reset:             ENTER");
	mlx_string_put(fdf->init, fdf->win, 1450, 1060, MENU,
				   "to move map         :       1, 2, 3, 5");
	mlx_string_put(fdf->init, fdf->win, 1450, 1080, MENU,
				   "to change color     :                C");
	mlx_string_put(fdf->init, fdf->win, 1450, 1100, MENU,
				   "grow up/grow down   :              W/S");
	mlx_string_put(fdf->init, fdf->win, 1450, 1120, MENU,
				   "zoom ++             :   + or arrows up");
	mlx_string_put(fdf->init, fdf->win, 1450, 1140, MENU,
				   "zoom --             : - or arrows down");
	mlx_string_put(fdf->init, fdf->win, 1450, 1160, MENU,
				   "exit or close window:       (X) or ESC");
}

void ft_init_colors(t_fdf *fdf)
{
	fdf->cord.colors[0] = 15865546;
	fdf->cord.colors[1] = 8087790;
	fdf->cord.colors[2] = 3207702;
	fdf->cord.colors[3] = 15462934;
	fdf->cord.colors[4] = 15431760;
	fdf->cord.colors[5] = 5250600;
	fdf->cord.colors[6] = 15736144;
	fdf->cord.colors[7] = 1230728;
	fdf->cord.colors[8] = 874583;
	fdf->cord.colors[9] = 15441387;
	fdf->cord.colors[10] = 16777215;
	fdf->cord.colors[11] = 5250600;
}

int	deal_key(int key, t_fdf *fdf)
{
//	int i;

//	i = 0;
	mlx_clear_window(fdf->init, fdf->win);
//	printf("%d\n", key);
	if (key == 82 || key == 29)
		show_menu(fdf);
	if (key == 7 || key == 53)
	{
		system("leaks -q fdf > leaks.txt");
		exit(0);
	}
	if ((key == 69 || key == 126) && fdf->cord.step <= 100)
		fdf->cord.step += 1;
	if ((key == 78 || key == 125) && fdf->cord.step >= 5)
		fdf->cord.step -= 1;
	if (key == 13 && fdf->cord.z_s <= 40)
		fdf->cord.z_s += 1;
	if (key == 1 && fdf->cord.z_s >= -40)
		fdf->cord.z_s -= 1;
	if (key == 8)
	{
		if (fdf->cord.i >= 11)
			fdf->cord.i = 0;
		fdf->cord.color = fdf->cord.colors[fdf->cord.i];
		fdf->cord.else_color = fdf->cord.colors[fdf->cord.i + 1];
		fdf->cord.i++;
		printf("color %d\n", fdf->cord.color);
	}
	if ((key == 18 ||  key == 83) && fdf->cord.x_s >= 1)
		fdf->cord.x_s -= 10;
	if ((key == 23 ||  key == 87) && fdf->cord.y_s >= 1)
		fdf->cord.y_s -= 10;
	if ((key == 19 ||  key == 84) && fdf->cord.y_s <= 1100)
		fdf->cord.y_s += 10;
	if ((key == 20 ||  key == 85) && fdf->cord.x_s <= 1900)
		fdf->cord.x_s += 10;
	ft_paint_fdf(fdf);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	fdf = (t_fdf*)malloc(sizeof(t_fdf));
	if (argc != 2)
		ft_color_printf("C_REDUsage : ./fdf <filename> [ case_size z_size ]\nC_of");
	else
	{
		if (ft_fdf(argv[1], fdf, 0) == 0)
		{
			system("leaks -q fdf > leaks.txt");
			return 0;
		}
		fdf->init = mlx_init();
		fdf->win = mlx_new_window(fdf->init, 2000, 1200, "fdf");
		ft_paint_fdf(fdf);
		ft_init_colors(fdf);
		mlx_hook(fdf->win, 2, 0, deal_key, fdf);
		mlx_hook(fdf->win, 17, 0, exit_fdf, NULL);
		mlx_loop(fdf->init);
	}
	system("leaks -q fdf > leaks.txt");
	return 0;
}
