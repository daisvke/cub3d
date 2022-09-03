/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2_fill_parser_buf.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:48:39 by lchan             #+#    #+#             */
/*   Updated: 2022/09/03 17:43:26 by lchan            ###   ########.fr       */
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

int	__add_in_err_buf(t_parser *parser, int error_type)
{
	if (parser->err_buf_index < PARSER_BUFFER_SIZE)
	{
		parser->err_buf[parser->err_buf_index][0] = parser->gnl_cnt;
		parser->err_buf[parser->err_buf_index][1] = error_type;
		parser->err_buf_index++;
	}
	if (error_type < ERR_GIBBERISH)
		parser->blocking_err_flag |= (1<<error_type);
	if (parser->line)
	{
		free(parser->line);
		parser->line = NULL;
	}
	return (1);
}

void	__update_err_flag(t_parser *parser, int flag)
{
	int	tmp;

	tmp = flag;
	tmp -= flag &= ~15;
	if ((tmp != 15))
		parser->blocking_err_flag |= (1<<ERR_TEXTURE_KEY_MISSING);
	flag |= 15;
	if ((flag != 63))
		parser->blocking_err_flag |= (1<<ERR_FC_KEY_MISSING);
}

int	__check_map_is_last(t_parser *parser, int info_flag)
{
	int	last_info_line;
	int	i;

	i = -1;
	last_info_line = 0;
	while (++i < 6)
		if (info_flag & (info_flag<<i)
		&& parser->info_buf_line[i] > last_info_line)
			last_info_line = parser->info_buf_line[i];
	i = -1;
	while (++i < parser->map_buf_index)
		if (last_info_line > parser->map_line_buf[i])
			return (-1);
	return (0);
}

/*************************************
 * 63 means all 6 first bits are set;
 * ***********************************/
int	__fill_parser_buf(t_parser *parser, int fd)
{
	if (fd > -1)
	{
		__pick_line_set_type(fd, parser);
		while (parser->type != TYPE_EOF)
		{
			__parse_line(parser, parser->line);
			__pick_line_set_type(fd, parser);
		}
		if (parser->gnl_cnt == 1)
			__add_in_err_buf(parser, ERR_EMPTY_FILE);
		else if (__check_map_is_last(parser, parser->info_buf_flag))
			__add_in_err_buf(parser, ERR_MAP_MISPLACED);
	 	close (fd);
	}
	if (parser->info_buf_flag != 63)
		__update_err_flag(parser, parser->info_buf_flag);
	return (parser->blocking_err_flag);
}
