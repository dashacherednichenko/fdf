/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiven <dpiven@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 15:44:29 by dpiven            #+#    #+#             */
/*   Updated: 2019/02/28 15:44:30 by dpiven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_count_words(char const *s, char c)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			while (s[i] != c && s[i])
				i++;
			x++;
		}
	}
	return (x);
}

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
