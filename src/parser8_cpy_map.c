/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser8_cpy_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 22:10:43 by lchan             #+#    #+#             */
/*   Updated: 2022/09/04 22:05:43 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**__init_env_map(t_parser *parser)
{
	char	**map;
	int		i;

	i = -1;
	map = malloc(sizeof(char *) * (parser->map_max_y + 1));
	if (map)
	{
		while (++i < parser->map_max_y)
		{
			map[i] = malloc(sizeof(char) * (parser->map_max_x + 1));
			c3d_memset(map[i], 0, parser->map_max_x);
			//printf("map[%d] = %.*s\n", i, parser->map_max_x, map[i]);
			if (!map[i])
			{
				map = __freetab_index(map, 0, NO_INDEX);
				break ;
			}
		}
		map[i] = NULL;
	}
	return (map);
}

char	**__map_cpy(t_parser *parser, char **env_map)
{
	char	*to_cpy;
	char	*dst;
	int		i;

	i = -1;
	while (++i < parser->map_max_y)
	{
		to_cpy = parser->map_buf[i];
		dst = env_map[i];
		while (*to_cpy != '\n')
			*dst++ = *to_cpy++;
		*dst = '\0';
	}
	env_map[i] = NULL;

	// char **tmp;
	// tmp = env_map;
	// while (*tmp)
	// 	printf("%s\n", *tmp++);
	return (env_map);
}

int	__cpy_map_to_env(t_parser *parser, t_c3d *env)
{
	char	**map;

	map = __init_env_map(parser);
	if (!map)
		c3d_add_to_env_exit(parser, env);
	env->map = __map_cpy(parser, map);
	if (!env->map)
		return (update_err_flag(parser, ERR_MAP_UNABLE_TO_CPY));
	return (0);
}
	//__freetab_index(parser->map_buf, parser->map_buf_index, 0); //to free parser_map
	//map = __freetab_index(map, 0, 1); //to free env->map
