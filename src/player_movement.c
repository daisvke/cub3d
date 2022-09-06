/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 03:43:32 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/09/05 18:00:45 by mint             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	c3d_check_obstacles_and_move_up(char **map, t_player *player)
{
	int	x;
	int	y;

	x = player->pos.x + player->dir.x * (player->speed * 12);
	y = player->pos.y + player->dir.y * (player->speed * 12);
	if (map[y][x] == '0' || map[y][x] == 'X')
	{
		player->pos.x += player->dir.x * player->speed;
		player->pos.y += player->dir.y * player->speed;
	}
}

void	c3d_check_obstacles_and_move_down(char **map, t_player *player)
{
	int	x;
	int	y;

	x = player->pos.x - player->dir.x * (player->speed * 12);
	y = player->pos.y - player->dir.y * (player->speed * 12);
	if (map[y][x] == '0' || map[y][x] == 'X')
	{
		player->pos.x -= player->dir.x * player->speed;
		player->pos.y -= player->dir.y * player->speed;
	}
}

void	c3d_check_obstacles_and_move_left(char **map, t_player *player)
{
	int	x;
	int	y;

	x = player->pos.x + player->dir.y * (player->speed * 12);
	y = player->pos.y - player->dir.x * (player->speed * 12);
	if (map[y][x] == '0' || map[y][x] == 'X')
	{
		player->pos.x += player->dir.y * player->speed;
		player->pos.y -= player->dir.x * player->speed;
	}
}

void	c3d_check_obstacles_and_move_right(char **map, t_player *player)
{
	int	x;
	int	y;

	x = player->pos.x - player->dir.y * (player->speed * 12);
	y = player->pos.y + player->dir.x * (player->speed * 12);
	if (map[y][x] == '0' || map[y][x] == 'X')
	{
		player->pos.x -= player->dir.y * player->speed;
		player->pos.y += player->dir.x * player->speed;
	}
}
