/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiven <dpiven@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:37:04 by dpiven            #+#    #+#             */
/*   Updated: 2019/02/27 16:37:06 by dpiven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int ft_is_color(char *s, int ii)
{
	if (strncmp(&s[ii], "0x", 2))
	{
//		printf("\nERRR%s\n", &s[ii]);
		return (0);
	}
	ii += 2;
	while (s[ii] != ' ' && s[ii] != '\n' && s[ii] != '\0')
	{
//		printf("\nY%s\n", &s[ii]);
		if (ft_isdigit(s[ii]) || ft_strchr("abcdefABCDEF\n", s[ii]))
		{
//			printf("\nT%c\n", s[ii]);
			ii++;
		}
		else
			return (0);
	}
//	printf("\nII %d\n", ii);
	return (ii);
}

int ft_validmap(char **l, int i, t_fdf *fdf)
{
	int ii;
	char *s;

	ii = 0;
	if (i == 0)
		fdf->w = ft_count_words(*l, ' ');
	else
	{
		if (fdf->w != ft_count_words(*l, ' '))
			return (0);
	}
	s = *l;
	while(ii < fdf->w)
	{
		if (ft_isdigit(s[ii]) || s[ii] == ' ' || s[ii] == '-' || s[ii] == '\n')
			ii++;
		else if (s[ii] == ',')
		{
			ii++;
//			printf("\nTTTT%s\n", &s[ii]);
			if ((ii = ft_is_color(s, ii)) == 0)
				return (0);
		}
		else
			return (0);
	}
//	printf("%d\n", fdf->w);
	return (1);
}

int	**ft_malloc_mtrx(t_fdf *fdf)
{
	int i;
	int **mtrx;

	i = 0;
	mtrx = (int**)malloc(sizeof(int*) * fdf->h);
	while (i < fdf->h)
	{
		mtrx[i] = (int*)malloc(sizeof(int) * fdf->w);
		i++;
	}
	return (mtrx);
}

int ft_fdf(char *s, t_fdf *fdf)
{
	int		fd;
	int		i;
	char	*l;

	i = 0;
	if ((open(s, O_DIRECTORY)) > 0)
	{
		ft_color_printf("C_REDIT IS A DIRECTORY C_GRN%s\nC_of", s);
		return (0);
	}
	if (ft_strstr(s, ".fdf") == 0)
	{
		ft_color_printf("C_REDNo file C_GRN%s\nC_of", s);
		return (0);
	}
	fd = open(s, O_RDONLY);
	if (fd < 0)
	{
		ft_color_printf("C_REDNo file C_GRN%s\nC_of", s);
		return (0);
	}
	while ((get_next_line(fd, &l)) > 0)
	{
		printf("%s\n", l);
		if (ft_validmap(&l, i, fdf) == 0)
		{
			ft_color_printf("C_REDERROR in map C_GRN%s\nC_of", s);
			return (0);
		}
		free (l);
		i++;
	}
	fdf->h = i;
	printf("%d\n", fdf->h);
	return (1);
}
