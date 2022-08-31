/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:48:39 by lchan             #+#    #+#             */
/*   Updated: 2022/08/31 18:33:35 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//char	*__skip_space()

void	__pick_line_set_type(int fd, t_parser *parser)
{
	parser->line = get_next_line(fd);
	parser->gnl_cnt++;
	while (__check_type(parser->line, &parser->type) == TYPE_USELESS)
	{
		free(parser->line);
		parser->line = get_next_line(fd);
		parser->gnl_cnt++;
	}
}

int	__check_map(t_c3d *env, t_player *player, int fd)
{
	t_parser	parser;
	(void)		player;
	(void)		env;

	c3d_memset(&parser, 0, sizeof(t_parser));
	if (fd > -1)
	{
		__pick_line_set_type(fd, &parser);
		while (parser.type != TYPE_EOF)
		{
			__parse_line(&parser, parser.line);
			__pick_line_set_type(fd, &parser);
		}
		if (parser.gnl_cnt == 1)
			parser.err |= (1<<ERR_EMPTY_MAP);
	// 	close (fd);
	// 	if (__check_info_validity(&parser))
	// 		__add_info_to_env(&parser, env);
	}
	return (parser.err);
}
