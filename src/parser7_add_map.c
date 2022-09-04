/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser7_add_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:05:25 by lchan             #+#    #+#             */
/*   Updated: 2022/09/04 22:23:09 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	update_err_flag(t_parser *parser, int err_nbr)
{
	parser->blocking_err_flag |= (1<<err_nbr);
	return(parser->blocking_err_flag);
}

int	__check_cutted_map(t_parser *parser, t_c3d *env)
{
	int	i;
	int	j;
	int	*map_line;
	(void) env;

	i = -1;
	j = i + 1;
	map_line = parser->map_line_buf;
	while (j < parser->map_buf_index - 1)
	{
		if (map_line[++i] + 1 != map_line[++j])
			return (update_err_flag(parser, ERR_MAP_CUTTED));
	}
	return (0);
}

int	__check_player(t_parser *parser, t_c3d *env)
{
	int		player_flag;
	char	**map;
	char	*tmp;
	(void) env;

	player_flag = 0;
	map = parser->map_buf;
	while (*map)
	{
		tmp = *map++;
		while (*tmp)
		{
			if (ft_strchr_b("NSWE", *tmp) == FOUND)
				player_flag++;
			tmp++;
		}
	}
	if (player_flag == 0)
		return (update_err_flag(parser, ERR_MAP_NO_PLAYER));
	else if (player_flag > 1)
		return (update_err_flag(parser, ERR_MAP_MULTI_PLAYER));
	return (0);
}

int	__check_surrounding_cells(char **map, int x, int y)
{
	if (x == 0 || y == 0)
		return (-1);
	if ((map[y][x + 1] == '\0' || map[y][x + 1] == ' ')
	|| (map[y][x - 1]  == '\0' || map[y][x - 1] == ' ')
	|| (map[y + 1][x] == '\0' || map[y + 1][x] == ' ' )
	|| (map[y - 1][x] == '\0' || map[y - 1][x] == ' '))
		return (-1);
	return (0);
}

int	__check_if_open_map(t_parser *parser, t_c3d *env)
{
	int	y;
	int	x;
	char	**map;

	map = env->map;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (ft_strchr_b("0SEWN", map[y][x]) == FOUND
			&& __check_surrounding_cells(map, x, y))
				return (update_err_flag(parser, ERR_MAP_BORDERS));
		}
	}
	return (0);
}

void	__set_player_dir(t_player *player, char orient)
{
	if (orient == 'N')
	{
		player->dir.x = 0.0;
		player->dir.y = -1.0;
		player->cam_plane.x = 0.66;
		player->cam_plane.y = 0.0;
	}
	else if (orient == 'S')
	{
		player->dir.x = 0.0;
		player->dir.y = 1.0;
		player->cam_plane.x = -0.66;
		player->cam_plane.y = 0.0;
	}
	else if (orient == 'W')
	{
		player->dir.x = -1.0;
		player->dir.y = 0.0;
		player->cam_plane.x = 0.0;
		player->cam_plane.y = -0.66;
	}
	else if (orient == 'E')
	{
		player->dir.x = 1.0;
		player->dir.y = 0.0;
		player->cam_plane.x = 0.0;
		player->cam_plane.y = 0.66;
	}
}

int	__update_player_position(t_c3d *env, char **map)
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
				env->player.pos.x = x;
				env->player.pos.y = y;
				__set_player_dir(&env->player, map[y][x]);
				return (0);
			}
		}
	}
	return (-1);
}

int	c3d_add_map_to_env(t_parser *parser, t_c3d *env)
{
	int	i;
	int ((*__check_map[4])(t_parser *parser, t_c3d *env));

	__check_map[0] = &__check_player;
	__check_map[1] = &__check_cutted_map;
	__check_map[2] = &__cpy_map_to_env;
	__check_map[3] = &__check_if_open_map;

	i = -1;
	if (parser->map_max_x < 3 || parser->map_max_y < 3)
		return (update_err_flag(parser, ERR_MAP_TOO_SMALL));
	while (++i < 4)
		if (__check_map[i](parser, env))
			return (-1);
	__update_player_position(env, env->map);
	return 0;
}

	// printf("max_x = %d\n", parser->map_max_x);
	// printf("max_y = %d\n", parser->map_max_y);
