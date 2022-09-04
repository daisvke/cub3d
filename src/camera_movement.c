/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 03:43:30 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/09/04 05:35:09 by mint             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	c3d_look_left(t_player *p)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = p->dir.x;
	p->dir.x = p->dir.x * cos(-p->speed) - p->dir.y * sin(-p->speed);
	p->dir.y = old_dirx * sin(-p->speed) + p->dir.y * cos(-p->speed);
	old_planex = p->cam_plane.x;
	p->cam_plane.x = p->cam_plane.x * cos(-p->speed) \
		- p->cam_plane.y * sin(-p->speed);
	p->cam_plane.y = old_planex * sin(-p->speed)
		+ p->cam_plane.y * cos(-p->speed);
}

void	c3d_look_right(t_player *p)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = p->dir.x;
	p->dir.x = p->dir.x * cos(p->speed) - p->dir.y * sin(p->speed);
	p->dir.y = old_dirx * sin(p->speed) + p->dir.y * cos(p->speed);
	old_planex = p->cam_plane.x;
	p->cam_plane.x = p->cam_plane.x * cos(p->speed) \
		- p->cam_plane.y * sin(p->speed);
	p->cam_plane.y = old_planex * sin(p->speed) \
		+ p->cam_plane.y * cos(p->speed);
}
