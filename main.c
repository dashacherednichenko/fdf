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

int	deal_key(int key, void *param)
{
	ft_putchar('X');
//	mlx_pixel_put(mlx_ptr,win_ptr, 300, 150, 0xFFFFFF);
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
			system("leaks -q fdf");
			return 0;
		}
		fdf->init = mlx_init();
		fdf->win = mlx_new_window(fdf->init, 2000, 1200, "fdf");
		ft_paint_fdf(fdf);
//		mlx_pixel_put(fdf->init, fdf->win, 300, 250, 0xFFFFFF);
//		mlx_pixel_put(fdf->init, fdf->win, 300, 300, 0xFFFFFF);
//		mlx_key_hook(fdf->win, deal_key, (void *)0);
		mlx_loop(fdf->init);
	}
	system("leaks -q fdf");
	return 0;
}
