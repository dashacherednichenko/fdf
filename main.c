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
	void	*mlx_ptr;
	void	*win_ptr;
//	char	*line;
	t_fdf	*fdf;

//	line = NULL;
	fdf = (t_fdf*)malloc(sizeof(t_fdf));
	if (argc != 2)
		ft_color_printf("C_REDUsage : ./fdf <filename> [ case_size z_size ]\nC_of");
	else
	{
//		mlx_ptr = mlx_init();
//		win_ptr = mlx_new_window(mlx_ptr, 2000, 1200, "fdf");
//		mlx_pixel_put(mlx_ptr, win_ptr, 300, 250, 0xFFFFFF);
//		mlx_pixel_put(mlx_ptr, win_ptr, 300, 300, 0xFFFFFF);
//		mlx_key_hook(win_ptr, deal_key, (void *)0);
//		mlx_loop(mlx_ptr);
		if (ft_fdf(argv[1], fdf) == 0)
		{
			system("leaks -q fdf");
			return 0;
		}
	}
	system("leaks -q fdf");
	return 0;
}
