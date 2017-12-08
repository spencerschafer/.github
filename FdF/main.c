/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschafer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 13:26:29 by sschafer          #+#    #+#             */
/*   Updated: 2017/12/07 13:27:19 by sschafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //printf()
#include "libft.h" //libft functions
#include "mlx.h"
#include "fdf.h"
#include <fcntl.h>
#include <math.h>
/*
 ** Function that closes program window upon 'esc' key being pressed.
 */

int	close(int keycode)
{
	if (keycode == 53)
		exit(0);
	return (0);
}

void	dimension(char ***map, int *x, int *y)
{
	int x_c;
	int y_c;

	x_c = 0;
	y_c = 0;
	while (map[y_c][x_c])
		++x_c;
	while (map[y_c])
		++y_c;
	*x = x_c;
	*y = y_c;
}

int				main(int argc, char **argv)
{
	if (argc == 2)
	{
		int			win_x;
		int			win_y;
		void 		*mlx;
		void 		*window;
		char		***map = NULL;

		map = ft_open(map, argv[1]);

		//opening window
		win_x = 0;
		win_y = 0;
		dimension(map, &win_x, &win_y);
		printf("x: %d\ny: %d\n", win_x, win_y);
		win_x *= 28;
		win_y *= 14;
		mlx = mlx_init();

		window = mlx_new_window(mlx, win_x, win_y, "FdF");
		//window = mlx_new_window(mlx, x * 28, y * 50, "FdF");

		float x, y, x1, y1, x2, y2, dx, dy, step;
		int i;

		x1 = win_x / 2;
		x2 = win_x / 2 + 200;
		y1 = 10;
		y2 = win_y / 2 + 200;
		dx = x2 - x1;
		dy = y2 - y1;

		if(dx >= dy)
			step = dx;
		else
			step = dy;

		dx = dx / step;
		dy = dy / step;

		x = x1;
		y = y1;

		i = 1;
		while( i<= step)
		{
			mlx_pixel_put(mlx, window, x, y, 0xFFFFFF);
			//putpixel(x,y,5);
			x += dx;
			y += dy;
			++i;
		}
		mlx_key_hook(window, close, 0); // exit program
		mlx_loop(mlx);
	}
	return (0);
}

