/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 03:43:27 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/09/04 05:37:47 by mint             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	c3d_draw_square(t_c3d *env, int startx, int starty, int color)
{
	int	wall;
	int	y;
	int	x;

	wall = 4;
	y = 0;
	while (y < wall)
	{
		x = 0;
		while (x < wall)
		{
			env->buffer[starty * wall + y][startx * wall + x] = color;
			++x;
		}
		++y;
	}
}

void	c3d_draw_map(t_c3d *env, char **map, int playerx, int playery)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1'
				|| map[y][x] == 'X'
				|| (y == playery && x == playerx))
			{
				if (map[y][x] == '1')
					color = 0xFFFFFF;
				else
					color = 0xFF0000;
				c3d_draw_square(env, 5 + x, 5 + y, color);
			}
			++x;
		}
		++y;
	}
}

void	c3d_draw_on_screen(t_c3d *env, t_mlx *mlx)
{
	int	x;
	int	y;

	y = 0;
	while (y < mlx->screenh)
	{
		x = 0;
		while (x < mlx->screenw)
		{
			mlx->canvas.addr[y * mlx->screenw + x] = env->buffer[y][x];
			++x;
		}
		++y;
	}
	mlx_put_image_to_window(\
		mlx->mlx_ptr, mlx->win_ptr, mlx->canvas.mlx_img, 0, 0);
}

void	c3d_render_line_to_buffer(t_c3d *env, t_line line, t_ray ray, int x)
{
	int	y;

	y = 0;
	while (y < line.draw_start)
	{
		env->buffer[y][x] = env->ceiling.color;
		++y;
	}
	c3d_draw_wall_texture_on_line(env, &line, ray, x);
	y += line.lineheight;
	while (y >= 0 && y < env->mlx.screenh)
	{
		env->buffer[y][x] = env->floor.color;
		++y;
	}
}
