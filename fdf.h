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

# include "./libft/libft.h"
# include <mlx.h>
# include <math.h>

typedef struct		s_cord
{
	int				x_s;
	int				y_s;
	int				x0;
	int				y0;
	int				x1;
	int				y1;
	char 			fast_l;
	int				sign_x;
	int				sign_y;
	double			step;
	int				color;
}					t_cord;

typedef struct		s_fdf
{
	void			*init;
	void			*win;
	int				w;
	int				h;
	int				**map;
	t_cord			cord;
}					t_fdf;

int					ft_fdf(char *s, t_fdf *fdf, int i);
int					ft_validmap(char **line, int i, t_fdf *fdf);
int					ft_count_words(char const *s, char c);
t_fdf				*ft_malloc_mtrx(t_fdf *fdf);
t_fdf				*ft_create_mtrx(t_fdf *fdf, char *s);
int					*ft_toint(char *s, t_fdf *fdf, int x);
int 				ft_paint_fdf(t_fdf *fdf);

#endif
