/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 03:43:27 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/08/31 23:46:43 by dtanigaw         ###   ########.fr       */
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

double	c3d_get_wall_xpos(t_ray ray, t_coord p1_pos)
{
	double		wall_x;

	if (ray.side == 0)
		wall_x = p1_pos.y + ray.perp_walldist * ray.diry;
	else
		wall_x = p1_pos.x + ray.perp_walldist * ray.dirx;
	wall_x -= floor(wall_x);
	return (wall_x);
}

int	c3d_get_texture_xpos(t_coord p1_pos, t_ray ray)
{
	double	wall_x;
	int		tex_x;

	wall_x = c3d_get_wall_xpos(ray, p1_pos);
	tex_x = (int)(wall_x * (double)_TEX_SIZE);
	if (ray.side == 0 && ray.dirx > 0)
		tex_x = _TEX_SIZE - tex_x - 1;
	if (ray.side == 1 && ray.diry < 0)
		tex_x = _TEX_SIZE - tex_x - 1;
	return (tex_x);
}

static void	c3d_get_wall_orientation(t_line *tex_line, t_ray ray)
{
	if (ray.side == 0 && ray.dirx < 0)
		tex_line->orientation = TYPE_NO;
	if (ray.side == 0 && ray.dirx >= 0)
		tex_line->orientation = TYPE_SO;
	if (ray.side == 1 && ray.diry < 0)
		tex_line->orientation = TYPE_EA;
	if (ray.side == 1 && ray.diry >= 0)
		tex_line->orientation = TYPE_WE;
}

void	c3d_set_wall_texture(t_c3d *env, t_line *tex_line, t_ray ray, int x)
{
	double	step;
	t_coord	tex;
	double	tex_pos;
	int		y;
	int		color;

	tex.x = c3d_get_texture_xpos(env->player.pos, ray);
	step = 1.0 * _TEX_SIZE / tex_line->lineheight;
	tex_pos = (tex_line->draw_start - env->mlx.screenh / 2
		+ tex_line->lineheight / 2) * step;
	c3d_get_wall_orientation(tex_line, ray);
	y = tex_line->draw_start;
	while (y < tex_line->draw_end)
	{
		tex.y = (int)tex_pos & (_TEX_SIZE - 1);
		tex_pos += step;
		color = env->textures[tex_line->orientation][_TEX_SIZE * (int)tex.y + (int)tex.x];
		if (ray.side == 1)
			color = (color >> 1) & 8355711;
		env->buffer[y][x] = color;
		++y;
	}
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
	c3d_set_wall_texture(env, &line, ray, x);
	y += line.lineheight;
	while (y < env->mlx.screenh)
	{
		env->buffer[y][x] = env->ceiling.color; 
		++y;
	}
}
