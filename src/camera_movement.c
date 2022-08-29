/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 03:43:30 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/08/29 03:43:54 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	c3d_look_left(t_player *p)
{
	double old_dirx;
	double old_planex;

	old_dirx = p->dir.x;
	p->dir.x = p->dir.x * cos(-_SPEED) - p->dir.y * sin(-_SPEED);
	p->dir.y = old_dirx * sin(-_SPEED) + p->dir.y * cos(-_SPEED);
	old_planex = p->cam_plane.x;
	p->cam_plane.x = p->cam_plane.x * cos(-_SPEED) \
		- p->cam_plane.y * sin(-_SPEED);
	p->cam_plane.y = old_planex * sin(-_SPEED) + p->cam_plane.y * cos(-_SPEED);
}

void	c3d_look_right(t_player *p)
{
	double old_dirx;
	double old_planex;

	old_dirx = p->dir.x;
	p->dir.x = p->dir.x * cos(_SPEED) - p->dir.y * sin(_SPEED);
	p->dir.y = old_dirx * sin(_SPEED) + p->dir.y * cos(_SPEED);
	old_planex = p->cam_plane.x;
	p->cam_plane.x = p->cam_plane.x * cos(_SPEED) \
		- p->cam_plane.y * sin(_SPEED);
	p->cam_plane.y = old_planex * sin(_SPEED) + p->cam_plane.y * cos(_SPEED);
}
