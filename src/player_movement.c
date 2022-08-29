/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 03:43:32 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/08/29 03:43:54 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	c3d_check_obstacles_and_move_up(char **map, t_player *player)
{
	int	x;
	int	y;

	x = player->pos.x + player->dir.x * _SPEED;
	y = player->pos.y + player->dir.y * _SPEED;
	if (map[y][x] == '0')
	{
		player->pos.x += player->dir.x * _SPEED;
		player->pos.y += player->dir.y * _SPEED;
	}
}

void	c3d_check_obstacles_and_move_down(char **map, t_player *player)
{
	int	x;
	int	y;

	x = player->pos.x - player->dir.x * _SPEED;
	y = player->pos.y - player->dir.y * _SPEED;
	if (map[y][x] == '0')
	{
		player->pos.x -= player->dir.x * _SPEED;
		player->pos.y -= player->dir.y * _SPEED;
	}
}

void	c3d_check_obstacles_and_move_left(char **map, t_player *player)
{
	int	x;
	int	y;

	x = player->pos.x + player->dir.y * _SPEED;
	y = player->pos.y - player->dir.x * _SPEED;
	if (map[y][x] == '0')
	{
		player->pos.x += player->dir.y * _SPEED;
		player->pos.y -= player->dir.x * _SPEED;
	}
}

void	c3d_check_obstacles_and_move_right(char **map, t_player *player)
{
	int	x;
	int	y;

	x = player->pos.x - player->dir.y * _SPEED;
	y = player->pos.y + player->dir.x * _SPEED;
	if (map[y][x] == '0')
	{
		player->pos.x -= player->dir.y * _SPEED;
		player->pos.y += player->dir.x * _SPEED;
	}
}