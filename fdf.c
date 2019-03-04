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

int	ft_printmap(t_fdf *fdf)
{
	int x;
	int y;

	x = 0;
	while (x < fdf->h)
	{
		y = 0;
		while (y < fdf->w)
		{
			ft_printf("%3d ", fdf->map[x][y]);
			y++;
		}
		ft_printf("\n");
		x++;
	}
	return (0);
}

int	ft_is_color(char *s, int ii)
{
	if (strncmp(&s[ii], "0x", 2))
		return (0);
	ii += 2;
	while (s[ii] != ' ' && s[ii] != '\n' && s[ii] != '\0')
	{
		if (ft_isdigit(s[ii]) || ft_strchr("abcdefABCDEF\n", s[ii]))
		{
			ii++;
		}
		else
			return (0);
	}
	return (ii);
}

int	ft_validmap(char **l, int i, t_fdf *fdf)
{
	int		ii;
	char	*s;

	ii = 0;
	i == 0 ? fdf->w = ft_count_words(*l, ' ') : 0;
	if (i != 0 && fdf->w != ft_count_words(*l, ' '))
		return (0);
	s = *l;
	while (ii < fdf->w)
	{
		if (ft_isdigit(s[ii]) || s[ii] == ' ' || s[ii] == '-' || s[ii] == '\n')
			ii++;
		else if (s[ii] == ',')
		{
			ii++;
			if ((ii = ft_is_color(s, ii)) == 0)
				return (0);
		}
		else
			return (0);
	}
	return (1);
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

int	*ft_toint(char *s, t_fdf *fdf, int x)
{
	int y;
	int i;

	y = 0;
	i = 0;
	while (y < fdf->w && s[i])
	{
		if (ft_isdigit(s[i]) || s[i] == '-')
		{
			fdf->map[x][y] = ft_atoi(&s[i]);
			s[i] == '-' ? i++ : 0;
			while (ft_isdigit(s[i]) && s[i] != '\0')
				i++;
			if (s[i] == ',')
			{
				while (s[i] != ' ' && s[i])
					i++;
			}
			y++;
		}
		else
			i++;
	}
	return (fdf->map[x]);
}

t_fdf	*ft_create_mtrx(t_fdf *fdf, char *s)
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
	ft_printmap(fdf);
	return (fdf);
}

int	ft_fdf(char *s, t_fdf *fdf, int i)
{
	int		fd;
	char	*l;

	if ((open(s, O_DIRECTORY)) > 0)
	{
		ft_color_printf("C_REDIT IS A DIRECTORY C_GRN%s\nC_of", s);
		return (0);
	}
	fd = open(s, O_RDONLY);
	if (ft_strstr(s, ".fdf") == 0 || fd < 0)
	{
		ft_color_printf("C_REDNo file C_GRN%s\nC_of", s);
		return (0);
	}
	while (get_next_line(fd, &l) > 0)
	{
		if (ft_validmap(&l, i++, fdf) == 0)
		{
			free(l);
			ft_color_printf("C_REDERROR in map C_GRN%s\nC_of", s);
			return (0);
		}
		free(l);
	}
	fdf->h = i;
	close(fd);
	ft_create_mtrx(ft_malloc_mtrx(fdf), s);
	return (1);
}
