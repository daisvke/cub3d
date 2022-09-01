/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fill_parser_buf.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:48:39 by lchan             #+#    #+#             */
/*   Updated: 2022/09/01 16:44:53 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	__fill_parser_buf(t_parser *parser, int fd)
{
	c3d_memset(parser, 0, sizeof(t_parser));
	if (fd > -1)
	{
		__pick_line_set_type(fd, parser);
		while (parser->type != TYPE_EOF)
		{
			__parse_line(parser, parser->line);
			__pick_line_set_type(fd, parser);
		}
		if (parser->gnl_cnt == 1)
			__add_in_err_buf(parser, ERR_EMPTY_MAP);
	 	close (fd);
	}
	return (parser->blocking_err_index);
}
