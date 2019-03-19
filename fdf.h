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
# define MENU 8087790

# include "libft/libft.h"
# include "mlx.h"
# include <math.h>

typedef struct		s_bz_cord
{
	double			x;
	double			y;
}					t_bz_cord;

typedef struct		s_xy
{
	int				x;
	int				y;
}					t_xy;

typedef struct		s_cord
{
	int				x_s;
	int				y_s;
	int				z_s;
	int				x0;
	int				y0;
	int				x1;
	int				y1;
	int				sign_x;
	int				sign_y;
	double			step;
	int				colors[12];
	int				color;
	int				else_color;
	int				i;
}					t_cord;

typedef struct		s_fdf
{
	int				i;
	void			*init;
	void			*win;
	int				w;
	int				h;
	int				**map;
	double			**mtrx;
	int				midx;
	int				midy;
	t_cord			cord;
	t_bz_cord		newcord;
}					t_fdf;

int					ft_fdf(char *s, t_fdf *fdf, int i);
int					ft_validmap(char **line, int i, t_fdf *fdf);
int					ft_count_words(char const *s, char c);
t_fdf				*ft_malloc_mtrx(t_fdf *fdf);
t_fdf				*ft_create_map(t_fdf *fdf, char *s);
int					*ft_toint(char *s, t_fdf *fdf, int x);
int					ft_paint_fdf(t_fdf *fdf);
double				**ft_rotate_x(t_fdf *fdf, int sign);
double				**ft_rotate_y(t_fdf *fdf, int sign);
double				**ft_rotate_z(t_fdf *fdf, int sign);
double				**create_bz_mtrx(int i);
void				create_new_cord(t_fdf *fdf, int x, int y);
void				initial_values(t_fdf *fdf);
void				ft_free_double_mtrx(double **a);
double				**mltp_mtrx(double **a, double b[3][3], t_fdf *fdf);
int					ft_printmap(t_fdf *fdf);
void				ft_change_color(t_fdf *fdf);
void				show_menu(t_fdf *fdf);
int					deal_key(int key, t_fdf *fdf);
int					exit_fdf(void);

#endif
