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

int ft_validmap(char **l, int i, t_fdf *fdf)
{
	if (i == 0)
		fdf->w = ft_count_words(*l, ' ');
	else
	{
		if (fdf->w != ft_count_words(*l, ' '))
			return (0);
	}
//	printf("%d\n", fdf->w);
	return (1);
}

int ft_fdf(char *s, t_fdf *fdf)
{
	int fd;
	int i;
	char	*l;
	int t;

//	l = NULL;

	i = 0;
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
	while ((t = get_next_line(fd, &l)) > 0)
	{
		printf("%s\n", l);
		if (ft_validmap(&l, i, fdf) == 0 || t == 2)
		{
			ft_color_printf("C_REDERROR in map C_GRN%s\nC_of", s);
			return (0);
		}
		free (l);
		i++;
	}
	return (1);
}
