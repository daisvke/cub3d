/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser7_add_to_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:05:25 by lchan             #+#    #+#             */
/*   Updated: 2022/09/03 23:21:52 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	update_err_flag(t_parser *parser, int err_nbr)
{
	parser->blocking_err_flag |= (1<<err_nbr);
	return(parser->blocking_err_flag);
}

int	__check_map_size(t_parser *parser)
{
	if (parser->map_max_x < 3 || parser->map_max_y < 3)
		return (update_err_flag(parser, ERR_MAP_TOO_SMALL));

	return (0);
}

int	__check_cutted_map(t_parser *parser)
{
	int	i;
	int	j;
	int	*map_line;

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

int	__check_player(t_parser *parser)
{
	int		player_flag;
	char	**map;
	char	*tmp;

	player_flag = 0;
	map = parser->map_buf;
	while (*map)
	{
		tmp = *map++;
		while (*tmp)
		{
			if (ft_strchr_b("NSWE", *tmp) == 0)
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

// int	__check_open_map(t_parser *parser)
// {
// 	char **map;
// 	int	i;
// 	int	j;
// 	int	line_len;

// 	map = parser->map_buf;
// 	i = -1;
// 	j = -1;
// 	while (++i < parser->map_max_y)
// 	{
// 		line_len = ft_strlen(parser->map_buf[line_len]);
// 		while (++j <  parser->map_buf[i][j])
// 		parser->map_buf[i]
// 	}
// }

int	c3d_add_map_to_env(t_parser *parser, t_c3d *env)
{
	(void) env;
	int	i;
	int ((*__check_map[3])(t_parser *parser));

	__check_map[0] = &__check_map_size;
	__check_map[1] = &__check_player;
	__check_map[2] = &__check_cutted_map;
	//__check_map[3] = &__check_open_map;
	i = -1;
	while (++i < 3)
		if (__check_map[i](parser))
			return (-1);
	if (c3d_map_to_env(parser, env))
		return (-1);
	return 0;
}

	// printf("max_x = %d\n", parser->map_max_x);
	// printf("max_y = %d\n", parser->map_max_y);
