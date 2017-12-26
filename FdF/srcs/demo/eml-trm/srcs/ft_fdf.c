/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etermeau <etermeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 11:07:23 by etermeau          #+#    #+#             */
/*   Updated: 2015/01/02 13:58:53 by etermeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <mlx.h>
#include "../includes/fdf.h"

int			expose_hook(t_point ****tab, int i)
{
	i = 0;
	ft_draw_tab(tab, i);
	return (0);
}

//int			key_hook(int keycode, t_point ****tab)
int			key_hook(int keycode)
{
	//tab = tab;
	if (keycode == 65307)
		exit (0);
	return (0);
}

void		ft_init_mlx(t_point ****tab)
{
	ENV->mlx = mlx_init(); //man mlx
	ENV->win = mlx_new_window(ENV->mlx, 2200, 1300, "FDF"); //man mlx_new_window
	mlx_expose_hook(ENV->win, expose_hook, tab); //man mlx_loop
	mlx_key_hook(ENV->win, key_hook, tab); //man mlx_loop
	mlx_loop(ENV->mlx); //man mlx_loop
}

//TODO: possibly important for determining y value
int			ft_calcul(int tmp_z, int tmp_x, int tmp_y)
{
	//SPC = 15
	//DINCX = 0.6
	//DINCY = 0.6
	return ((-tmp_z + DINCX * tmp_x + DINCY * tmp_y) * SPC);
}

void		ft_fdf(t_point ****tab)
{
	int		tmp_x;
	int		tmp_y;
	int		tmp_z;
	int		i;
	int		j;

	i = 0;
	while ((*tab)[i])
	{
		j = 0;
		while ((*tab)[i][j])
		{
			//GPS_X = 50
			//GPS_Y = 2
			tmp_x = GPS_X + (*tab)[i][j]->x;
			tmp_y = GPS_Y + (*tab)[i][j]->y;
			//TODO: why divide by 9?

			tmp_z = (*tab)[i][j]->z / 9;

			//TODO: possibly important for determining y value
			//INCX = 1.2
			//INCY = 1.2
			(*tab)[i][j]->x = (SPC * (INCX * tmp_x - INCY * tmp_y));
			(*tab)[i][j]->y = ft_calcul(tmp_z, tmp_x, tmp_y);
			j++;
		}
		i++;
	}
	ft_init_mlx(tab);
}
