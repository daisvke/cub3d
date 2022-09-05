/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser7_add_player.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 21:26:04 by lchan             #+#    #+#             */
/*   Updated: 2022/09/05 21:37:06 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	c3d_set_player_dir(t_player *player, char orient)
{
	if (orient == 'N' || orient == 'S')
	{
		player->dir.x = 0.0;
		player->dir.y = DIR;
		player->cam_plane.x = CAM_PLANE;
		player->cam_plane.y = 0.0;
		if (orient == 'N')
			player->dir.y *= -1;
		else
			player->cam_plane.x = -1;
	}
	else if (orient == 'W' || orient == 'E')
	{
		player->dir.x = DIR;
		player->dir.y = 0.0;
		player->cam_plane.x = 0.0;
		player->cam_plane.y = CAM_PLANE;
		if (orient == 'W')
		{
			player->dir.x *= -1;
			player->cam_plane.y *= -1;
		}
	}
}

int	c3d_update_player_position(t_c3d *env, char **map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (ft_strchr_b("SEWN", map[y][x]) == FOUND)
			{
				env->player.pos.x = x + X_ADJUST;
				env->player.pos.y = y + Y_ADJUST;
				c3d_set_player_dir(&env->player, map[y][x]);
				map[y][x] = '0';
				return (0);
			}
		}
	}
	return (-1);
}
