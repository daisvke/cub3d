/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 03:43:27 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/08/29 03:43:53 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->canvas.mlx_img, 0, 0);
	for (int i=0; i < mlx->screenh; ++i)
		for (int j=0; j < mlx->screenw; ++j)
			env->buffer[i][j] = 0;
}

void	c3d_render_line_to_buffer(t_c3d *env, t_line line, t_ray ray, int x)
{
	int	y;

	y = 0;
	while (y < line.draw_start)
	{
		env->buffer[y][x] = env->floor.color; 
		++y;
	}
	y = line.draw_start;
	while (y <= line.draw_end)
	{
		if (ray.side == _YSIDE)
			env->buffer[y][x] = 0x00FF0000; 
		else
			env->buffer[y][x] = 0x0000FF00; 
		++y;
	}
	while (y < env->mlx.screenh)
	{
		env->buffer[y][x] = env->ceiling.color; 
		++y;
	}
}
