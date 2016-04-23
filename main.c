/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 18:42:53 by fnieto            #+#    #+#             */
/*   Updated: 2016/04/23 17:22:09 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		make_window(char *name, t_fractol *fractol, t_window *dest, int id)
{
	int i;

	dest->width = fractol->width;
	dest->height = fractol->height;
	dest->id = mlx_new_window(fractol->core, dest->width, dest->height, name);
	dest->canvasid = mlx_new_image(fractol->core, dest->width, dest->height);
	dest->canvas = (int*)mlx_get_data_addr(dest->canvasid, &i, &i, &i);
	dest->input = (t_input*)ft_memalloc(sizeof(t_input));
	dest->input->zoom = 0.03;
	dest->input->resx = fractol->width;
	dest->input->resy = fractol->height;
	dest->fractal_id = id;
	fractol->actnum++;
}

void		make_fractals(int *fractals, t_fractol *fractol)
{
	int			i;
	static char	*fracts[] = {"mandelbrot", "julia", "burning ship"};

	i = -1;
	while (++i < FRACTNUM)
		if (fractals[i])
			make_window(fracts[i], fractol, &(fractol->windows[i]), i);
		else
			fractol->windows[i].id = (void*)0;
}

void		make_params(int ac, char **av, t_fractol *fractol)
{
	int		i;
	int		fractals[FRACTNUM];

	i = -1;
	while (++i < ac)
		if (!ft_strcmp(av[i], "-res"))
		{
			if (ac - i < 3)
				ft_err("-res: not enough parameters");
			fractol->width = ft_atoi(av[++i]);
			fractol->height = ft_atoi(av[++i]);
			if (fractol->width < 100 || fractol->height < 100 ||
					fractol->width > 2000 || fractol->height > 2000)
				ft_err("-res: resolution must be between 100 and 2000");
		}
		else if (!ft_strcmp(av[i], "mandelbrot"))
			fractals[MANDELBROT] = 1;
		else if (!ft_strcmp(av[i], "julia"))
			fractals[JULIA] = 1;
		else if (!ft_strcmp(av[i], "burningship"))
			fractals[BURNINGSHIP] = 1;
		else if (!ft_strcmp(av[i], "-h"))
			ft_help();
	make_fractals(fractals, fractol);
}

void		hookup(t_fractol *fractol)
{
	int			i;
	t_window	*win;

	i = -1;
	while (++i < FRACTNUM)
	{
		win = &(fractol->windows[i]);
		if (win->id)
		{
			mlx_hook(win->id, 2, 4, &key_hook, win->input);
			mlx_hook(win->id, 4, 0, &mouse_hook, win->input);
			mlx_hook(win->id, 5, 0, &mouse_release_hook, win->input);
			mlx_hook(win->id, 6, 0, &cursor_hook, win->input);
		}
	}
}

int			main(int ac, char **av)
{
	t_fractol		fractol;

	fractol.core = mlx_init();
	fractol.width = 500;
	fractol.height = 500;
	fractol.actnum = 0;
	make_params(ac, av, &fractol);
	hookup(&fractol);
	mlx_loop_hook(fractol.core, &loop_hook, &fractol);
	if (fractol.actnum > 0)
		mlx_loop(fractol.core);
	else
		ft_help();
}
