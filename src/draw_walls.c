/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:21:21 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/09/09 20:46:05 by mint             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		tex_line->orientation = TYPE_WE;
	if (ray.side == 0 && ray.dirx >= 0)
		tex_line->orientation = TYPE_EA;
	if (ray.side == 1 && ray.diry < 0)
		tex_line->orientation = TYPE_NO;
	if (ray.side == 1 && ray.diry >= 0)
		tex_line->orientation = TYPE_SO;
}

void	c3d_draw_wall_texture_on_line(\
	t_c3d *env, t_line *tex_line, t_ray ray, int x)
{
	double	step;
	t_coord	tex;
	double	tex_pos;
	int		y;
	int		color;

	tex.x = c3d_get_texture_xpos(env->player.pos, ray);
	step = 1.0 * _TEX_SIZE / tex_line->lineheight;
	tex_pos = (tex_line->draw_start - env->mlx.screenh / 2 \
		+ tex_line->lineheight / 2) * step;
	c3d_get_wall_orientation(tex_line, ray);
	y = tex_line->draw_start;
	while (y < tex_line->draw_end)
	{
		tex.y = (int)tex_pos & (_TEX_SIZE - 1);
		tex_pos += step;
		color = env->textures[tex_line->orientation] \
			[_TEX_SIZE * (int)tex.y + (int)tex.x];
		if (ray.side == 1)
			color = (color >> 1) & 8355711;
		env->buffer[y][x] = color;
		++y;
	}
}
