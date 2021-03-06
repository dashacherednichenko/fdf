/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiven <dpiven@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:37:04 by dpiven            #+#    #+#             */
/*   Updated: 2019/03/19 19:35:50 by dpiven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_is_color(char *s, int ii)
{
	if (ft_strncmp(&s[ii], "0x", 2))
		return (0);
	ii += 2;
	while (s[ii] != ' ' && s[ii] != '\n' && s[ii] != '\0')
	{
		if (ft_isdigit(s[ii]) || ft_strchr("abcdefABCDEF\n", s[ii]))
			ii++;
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
	if ((i != 0 && fdf->w != ft_count_words(*l, ' ')) || fdf->w == 0)
		return (0);
	s = *l;
	while (s[ii])
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
			fdf->map[x][y] = fdf->map[x][y] > 300 ? 300 : fdf->map[x][y];
			fdf->map[x][y] = fdf->map[x][y] < -300 ? -300 : fdf->map[x][y];
			s[i] == '-' ? i++ : 0;
			while (ft_isdigit(s[i]) && s[i] != '\0')
				i++;
			if (s[i] == ',')
				while (s[i] != ' ' && s[i])
					i++;
			y++;
		}
		else
			i++;
	}
	return (fdf->map[x]);
}

int	ft_error_map(char **l, char *s)
{
	free(*l);
	ft_color_printf("C_REDERROR in map C_GRN%s\nC_of", s);
	return (0);
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
	if ((fd = open(s, O_RDONLY)) < 0)
	{
		ft_color_printf("C_REDNo file C_GRN%s\nC_of", s);
		return (0);
	}
	while (get_next_line(fd, &l) > 0)
	{
		if (ft_validmap(&l, i++, fdf) == 0)
			return (ft_error_map(&l, s));
		free(l);
	}
	fdf->h = i;
	close(fd);
	ft_create_map(ft_malloc_mtrx(fdf), s);
	return (1);
}
