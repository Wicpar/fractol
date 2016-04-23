/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 17:04:50 by fnieto            #+#    #+#             */
/*   Updated: 2016/04/23 17:22:41 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		greyfade(int iter, int maxiter, t_float *params)
{
	int color;

	color = (int)((iter * 255) / (t_float)maxiter);
	color &= 0xFF;
	color += (int)params[0] & 0;
	return ((color << 16) + (color << 8) + color);
}

int		psychofade(int iter, int maxiter, t_float *params)
{
	int color;

	color = maxiter;
	color += (int)params[0] & 0;
	return (0xFFFFFF & (iter * iter * iter));
}

int		color(int iter, int max, t_float *params, size_t ind)
{
	static t_col	funcs[] = {&greyfade, &psychofade};

	return ((*funcs[ind % (sizeof(funcs) / sizeof(t_col))])(iter, max, params));
}
