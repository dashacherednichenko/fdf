/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiven <dpiven@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 20:27:10 by dpiven            #+#    #+#             */
/*   Updated: 2019/03/18 20:27:11 by dpiven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_free_double_mtrx(double **a)
{
	int x;

	x = 0;
	while (x < 3)
		free(a[x++]);
	free(a);
}

t_fdf	*ft_malloc_mtrx(t_fdf *fdf)
{
	int i;

	i = 0;
	fdf->map = (int**)malloc(sizeof(int*) * fdf->h);
	while (i < fdf->h)
	{
		fdf->map[i] = (int*)malloc(sizeof(int) * fdf->w);
		i++;
	}
	return (fdf);
}

t_fdf	*ft_create_map(t_fdf *fdf, char *s)
{
	int		fd;
	int		x;
	char	*l;

	x = 0;
	fd = open(s, O_RDONLY);
	while (x < fdf->h && get_next_line(fd, &l) > 0)
	{
		fdf->map[x] = ft_toint(l, fdf, x);
		free(l);
		x++;
	}
	close(fd);
	return (fdf);
}

double	**create_bz_mtrx(int i)
{
	double	**bz_mtrx;

	bz_mtrx = (double**)malloc(sizeof(double*) * 3);
	while (i < 3)
		bz_mtrx[i++] = (double*)malloc(sizeof(double) * 3);
	bz_mtrx[0][0] = 1;
	bz_mtrx[0][1] = 0;
	bz_mtrx[0][2] = 0;
	bz_mtrx[1][0] = 0;
	bz_mtrx[1][1] = 1;
	bz_mtrx[1][2] = 0;
	bz_mtrx[2][0] = 0;
	bz_mtrx[2][1] = 0;
	bz_mtrx[2][2] = 1;
	return (bz_mtrx);
}
