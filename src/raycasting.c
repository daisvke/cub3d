/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 03:43:35 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/08/31 23:04:28 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	c3d_set_ray(t_mlx *mlx, t_ray *ray, t_player player, int x)
{
	double	camx;

	camx = 2 * x / (double)mlx->screenw - 1;
	ray->dirx = player.dir.x + player.cam_plane.x * camx;
	ray->diry = player.dir.y + player.cam_plane.y * camx;
	ray->mapx = (int)player.pos.x;
	ray->mapy = (int)player.pos.y;
	//ternaire
	ray->delta_distx = (ray->dirx == 0) ? 1e30 : fabs(1 / ray->dirx);
	ray->delta_disty = (ray->diry == 0) ? 1e30 : fabs(1 / ray->diry);
}

void	c3d_prepare_dda(t_ray *ray, t_coord pos)
{
	if (ray->dirx < 0)
	{
		ray->stepx = -1;
		ray->side_distx = (pos.x - ray->mapx) * ray->delta_distx;
	}
	else
	{
		ray->stepx = 1;
		ray->side_distx = (ray->mapx + 1 - pos.x) * ray->delta_distx;
	}
	if (ray->diry < 0)
	{
		ray->stepy = -1;
		ray->side_disty = (pos.y - ray->mapy) * ray->delta_disty;
	}
	else
	{
		ray->stepy = 1;
		ray->side_disty = (ray->mapy + 1 - pos.y) * ray->delta_disty;
	}
}

void	c3d_execute_dda(t_ray *ray, char **map)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_distx < ray->side_disty)
		{
			ray->side_distx += ray->delta_distx;
			ray->mapx += ray->stepx;
			ray->side = _XSIDE;
		}
		else
		{
			ray->side_disty += ray->delta_disty;
			ray->mapy += ray->stepy;
			ray->side = _YSIDE;
		}
		if (map[ray->mapy][ray->mapx] == '1')
			hit = 1;
	}
	if (ray->side == _XSIDE)
		ray->perp_walldist = ray->side_distx - ray->delta_distx;
	else if (ray->side == _YSIDE)
		ray->perp_walldist = ray->side_disty - ray->delta_disty;
}

void	c3d_set_line(t_mlx *mlx, t_ray ray, t_line *line)
{
	int	h;

	h = mlx->screenh;
	line->lineheight = (int)(mlx->screenh / ray.perp_walldist);
	line->draw_start = -line->lineheight / 2 + h / 2;
	if (line->draw_start < 0)
		line->draw_start = 0;
	line->draw_end = line->lineheight / 2 + h / 2;
	if (line->draw_end >= h)
		line->draw_end = h - 1;
}

void	c3d_execute_raycasting(t_c3d *env)
{
	int			x;
	t_ray		ray;
	t_line		line;

	x = 0;
	ft_memset(&ray, 0, sizeof(ray));
	while (x < env->mlx.screenw)
	{
		c3d_set_ray(&env->mlx, &ray, env->player, x);
		c3d_prepare_dda(&ray, env->player.pos);
		c3d_execute_dda(&ray, env->map);
		c3d_set_line(&env->mlx, ray, &line);
	//	env->zbuffer[x] = ray.perp_walldist;
		c3d_render_line_to_buffer(env, line, ray, x);
		++x;
	}
}
