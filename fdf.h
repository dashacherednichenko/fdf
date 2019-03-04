/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiven <dpiven@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:34:26 by dpiven            #+#    #+#             */
/*   Updated: 2019/02/27 16:34:28 by dpiven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "./libft/libft.h"
#include "mlx.h"

typedef struct		s_fdf
{
	int				w;
	int				h;
	int				**map;
}					t_fdf;

int					ft_fdf(char *s, t_fdf *fdf);
int 				ft_validmap(char **line, int i, t_fdf *fdf);
int					ft_count_words(char const *s, char c);
int					**ft_malloc_mtrx(t_fdf *fdf);

#endif