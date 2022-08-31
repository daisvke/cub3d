/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:48:39 by lchan             #+#    #+#             */
/*   Updated: 2022/08/31 13:14:36 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	__parse_line(t_parser *parser)
{
	printf("type = %d\n", parser->type);
	printf("line = %s\n", parser->line);
	free(parser->line);
}



int	__check_map(t_c3d *env, t_player *player, int fd)
{
	t_parser	parser;
	(void)		player;
	(void)		env;

	ft_memset(&parser, 0, sizeof(t_parser));
	if (fd > -1)
	{
		//parser.err |= (1<<ERR_EMPTY_MAP);
		__pick_line_set_type(fd, &parser);
		while (parser.type != TYPE_EOF)
		{
			__parse_line(&parser);
			__pick_line_set_type(fd, &parser);
		}
	// 	close (fd);
	// 	if (__check_info_validity(&parser))
	// 		__add_info_to_env(&parser, env);
	}
	return (parser.err);
}
