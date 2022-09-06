/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser7_add_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:05:25 by lchan             #+#    #+#             */
/*   Updated: 2022/09/06 18:15:42 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	c3d_check_cutted_map(t_parser *parser, t_c3d *env)
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
			return (c3d_update_err_flag(parser, ERR_MP_CUTTED));
	}
	return (0);
}

int	c3d_check_player(t_parser *parser, t_c3d *env)
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
			if (c3d_strchr_b(MAP_ORIENT_CHAR, *tmp) == FOUND)
				player_flag++;
			tmp++;
		}
	}
	if (player_flag == 0)
		return (c3d_update_err_flag(parser, ERR_MP_NO_PLAYER));
	else if (player_flag > 1)
		return (c3d_update_err_flag(parser, ERR_MP_MULTI_PLAYER));
	return (0);
}

int	c3d_check_surrounding_cells(char **map, int x, int y, int max_y)
{
	if (x == 0 || y == 0 || y == max_y - 1)
		return (-1);
	if ((map[y][x + 1] == '\0' || map[y][x + 1] == ' ')
	|| (map[y][x - 1] == '\0' || map[y][x - 1] == ' ')
	|| (map[y + 1][x] == '\0' || map[y + 1][x] == ' ' )
	|| (map[y - 1][x] == '\0' || map[y - 1][x] == ' '))
		return (-1);
	return (0);
}

int	c3d_check_if_open_map(t_parser *parser, t_c3d *env)
{
	int		y;
	int		x;
	char	**map;

	map = env->map;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (c3d_strchr_b("0SEWN", map[y][x]) == FOUND
			&& c3d_check_surrounding_cells(map, x, y, parser->map_max_y))
				return (c3d_update_err_flag(parser, ERR_MP_BORDERS));
		}
	}
	return (0);
}

int	c3d_add_map_to_env(t_parser *parser, t_c3d *env)
{
	int	i;
	int	((*c3d_check_map[4])(t_parser *parser, t_c3d *env));

	c3d_check_map[0] = &c3d_check_player;
	c3d_check_map[1] = &c3d_check_cutted_map;
	c3d_check_map[2] = &c3d_cpy_map_to_env;
	c3d_check_map[3] = &c3d_check_if_open_map;
	i = -1;
	if (parser->map_max_x < 3 || parser->map_max_y < 3)
		return (c3d_update_err_flag(parser, ERR_MP_TOO_SMALL));
	while (++i < 4)
		if (c3d_check_map[i](parser, env))
			return (-1);
	c3d_update_player_position(env, env->map);
	return (0);
}
