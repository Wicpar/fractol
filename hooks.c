/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 17:15:36 by fnieto            #+#    #+#             */
/*   Updated: 2016/04/23 17:23:09 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		loop_hook(void *params)
{
	static t_update	updates[] = {&u_mandelbrot, &u_julia, &u_ship};
	t_fractol		*fractol;
	int				i;
	t_window		*win;

	fractol = (t_fractol*)params;
	i = -1;
	while (++i < FRACTNUM)
	{
		win = &(fractol->windows[i]);
		if (win->id)
			(*updates[i])(win, fractol->core);
	}
	return ((int)params);
}

int		key_hook(int keycode, void *params)
{
	t_input *input;

	input = (t_input*)params;
	if (keycode == 24)
		input->iters++;
	else if (keycode == 27)
		input->iters--;
	else if (keycode == 49)
		input->option++;
	else if (keycode == 257)
		input->option--;
	else if (keycode == 51)
	{
		input->posx = 0;
		input->posy = 0;
	}
	else if (keycode == 53)
		exit(0);
	return ((int)params);
}

int		cursor_hook(int x, int y, void *params)
{
	static int	lx = 0;
	static int	ly = 0;
	int			dx;
	int			dy;
	t_input		*input;

	input = (t_input*)params;
	if (input->pbs & (1 << 1))
	{
		dx = x - lx;
		dy = y - ly;
		input->posx -= dx * input->zoom;
		input->posy -= dy * input->zoom;
	}
	if (input->pbs & (1 << 2))
	{
		input->curposx = x;
		input->curposy = y;
	}
	lx = x;
	ly = y;
	return ((int)(params = 0) & x & y);
}

int		mouse_hook(int button, int x, int y, void *params)
{
	t_input *in;

	in = (t_input*)params;
	in->pbs |= (1 << button);
	if (button == 6 || button == 5)
	{
		in->posx += (x - in->resx * 0.5) * in->zoom;
		in->posy += (y - in->resy * 0.5) * in->zoom;
		in->zoom *= 0.9;
		in->posx -= (x - in->resx * 0.5) * in->zoom;
		in->posy -= (y - in->resy * 0.5) * in->zoom;
	}
	else if (button == 4 || button == 7)
	{
		in->posx += (x - in->resx * 0.5) * in->zoom;
		in->posy += (y - in->resy * 0.5) * in->zoom;
		in->zoom *= 1.1;
		in->posx -= (x - in->resx * 0.5) * in->zoom;
		in->posy -= (y - in->resy * 0.5) * in->zoom;
	}
	return ((int)(params = 0) & button & x & y);
}

int		mouse_release_hook(int button, int x, int y, void *params)
{
	t_input *input;

	input = (t_input*)params;
	input->pbs &= ~(1 << button);
	return ((int)(params = 0) & button & x & y);
}
