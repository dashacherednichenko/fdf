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
#define USAGE "C_REDUsage : ./fdf <filename>[ case_size z_size ]\nC_of"

int		exit_fdf(void)
{
	system("leaks -q fdf");
	exit(0);
}

void	ft_init_colors(t_fdf *fdf)
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

void	ft_change_color(t_fdf *fdf)
{
	fdf->cord.i >= 11 ? fdf->cord.i = 0 : 0;
	fdf->cord.color = fdf->cord.colors[fdf->cord.i];
	fdf->cord.else_color = fdf->cord.colors[fdf->cord.i++ + 1];
}

int		main(int argc, char **argv)
{
	t_fdf	*fdf;

	fdf = (t_fdf*)malloc(sizeof(t_fdf));
	if (argc != 2)
		ft_color_printf(USAGE);
	else
	{
		if (ft_fdf(argv[1], fdf, 0) == 0)
		{
			system("leaks -q fdf");
			return (0);
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
	return (0);
}
