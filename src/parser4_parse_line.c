/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4_parse_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:15:55 by lchan             #+#    #+#             */
/*   Updated: 2022/09/06 18:29:17 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*c3d_skip_useless_char(char *line, int type, int opt)
{
	if (opt == 0)
	{
		while (*line == ' ')
			line++;
		if (type <= TYPE_EA)
			line += 3;
		else
			line += 2;
		while (*line == ' ')
			line++;
	}
	else
	{
		while (*line == ' ')
			line++;
		while (*line == '0')
			line++;
		if (!(*line >= '0' && *line <= '9'))
			line--;
	}
	return (line);
}

void	c3d_parse_texture(t_parser *parser, char *line, int type)
{
	int		i;

	if (!(parser->info_buf_flag & (1 << type)))
	{
		i = -1;
		while (line[++i] && c3d_strchr_b(" \n", line[i]) == -1)
		{
			parser->info_buf[type][i] = line[i];
			if (i == PATH_MAX
				&& c3d_add_in_err_buf(parser, ERR_TX_PATH_LENGH))
				break ;
		}
		parser->info_buf[type][i] = '\0';
		parser->info_buf_flag |= (1 << type);
		parser->info_buf_line[type] = parser->gnl_cnt;
	}
	else
		c3d_add_in_err_buf(parser, ERR_TX_MULTIDEF);
}

void	c3d_parse_color(t_parser *parser, char *line, int type)
{
	int		i;

	if ((parser->info_buf_flag & (1 << type)) == 0)
	{
		i = 0;
		while (*line && *line != '\n')
		{
			line = c3d_skip_useless_char(line, type, 1);
			while (*line >= '0' && *line <= '9')
				parser->info_buf[type][i++] = *(line++);
			if (*line == ',')
				parser->info_buf[type][i++] = *(line++);
			else if ((*line != '\n' && *line != ' ')
				&& c3d_add_in_err_buf(parser, ERR_FC_FORM))
				break ;
		}
		parser->info_buf[type][i] = '\0';
		parser->info_buf_flag |= (1 << type);
		parser->info_buf_line[type] = parser->gnl_cnt;
	}
	else
		c3d_add_in_err_buf(parser, ERR_FC_MULTIDEF);
}

void	c3d_parse_map(t_parser *parser, char *line, int type)
{
	int	line_len;

	(void) type;
	if (parser->map_buf_index < PARSER_BUFFER_SIZE - 1)
	{
		line_len = c3d_strlen(line) - 1;
		parser->map_buf[parser->map_buf_index] = line;
		parser->map_line_buf[parser->map_buf_index] = parser->gnl_cnt;
		parser->map_buf_index++;
		if (line_len > parser->map_max_x)
			parser->map_max_x = line_len;
		parser->map_max_y++;
		if (line_len >= MAP_MAX_LENGH || parser->map_max_y >= MAP_MAX_HEIGHT)
			c3d_add_in_err_buf(parser, ERR_MP_TOO_BIG);
	}
	else
		c3d_add_in_err_buf(parser, ERR_MP_TOO_BIG);
}

void	c3d_parse_line(t_parser *parser, char *line)
{
	void	((*c3d_parse_line[7])(t_parser *parser, char *line, int type));

	c3d_parse_line[TYPE_NO] = &c3d_parse_texture;
	c3d_parse_line[TYPE_SO] = &c3d_parse_texture;
	c3d_parse_line[TYPE_WE] = &c3d_parse_texture;
	c3d_parse_line[TYPE_EA] = &c3d_parse_texture;
	c3d_parse_line[TYPE_F] = &c3d_parse_color;
	c3d_parse_line[TYPE_C] = &c3d_parse_color;
	c3d_parse_line[TYPE_MAP] = &c3d_parse_map;
	if (parser->type <= TYPE_C)
		line = c3d_skip_useless_char(line, parser->type, 0);
	if (parser->type == TYPE_ERR)
		c3d_add_in_err_buf(parser, ERR_GIBBER);
	else
		c3d_parse_line[parser->type](parser, line, parser->type);
	if (parser->type != TYPE_MAP && parser->line)
		free(parser->line);
}
