/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 14:15:01 by fnieto            #+#    #+#             */
/*   Updated: 2016/04/23 17:20:04 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include "libft.h"
# include <stdlib.h>

# define FRACTNUM	3

# define MANDELBROT		0
# define JULIA			1
# define BURNINGSHIP	2

typedef	long double		t_float;

typedef	unsigned short	t_ushort;

typedef	struct			s_input
{
	t_float		zoom;
	t_float		posx;
	t_float		posy;
	int			curposx;
	int			curposy;
	int			resx;
	int			resy;
	int			pbs;
	t_ushort	iters;
	size_t		option;
}						t_input;

typedef	struct			s_window
{
	int			width;
	int			height;
	void		*id;
	int			*canvas;
	void		*canvasid;
	int			fractal_id;
	t_input		*input;
}						t_window;

typedef	void			(*t_update)(t_window*, void*);

typedef	int				(*t_col)(int, int, t_float*);

typedef	struct			s_fractol
{
	t_window	windows[FRACTNUM];
	int			actnum;
	int			width;
	int			height;
	void		*core;
}						t_fractol;

int						color(int iter, int max, t_float *params, size_t ind);
void					ft_err(char *str);
void					ft_help(void);
void					u_julia(t_window *win, void *core);
void					u_ship(t_window *win, void *core);
void					u_mandelbrot(t_window *win, void *core);
int						loop_hook(void *params);
int						key_hook(int keycode, void *params);
int						cursor_hook(int x, int y, void *params);
int						mouse_hook(int button, int x, int y, void *params);
int						mouse_release_hook(int b, int x, int y, void *params);

#endif
