/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4_parse_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:15:55 by lchan             #+#    #+#             */
/*   Updated: 2022/09/03 22:58:54 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*__skip_useless_char(char *line, int type, int opt)
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

void	__parse_texture(t_parser *parser, char *line, int type)
{
	int		i;

	if (!(parser->info_buf_flag & (1<<type)))
	{
		i = -1;
		while (line[++i] && ft_strchr_b(" \n", line[i]) == -1)
		{
			parser->info_buf[type][i] = line[i];
			if (i == PATH_MAX
			&& __add_in_err_buf(parser, ERR_TEXTURE_PATH_LENGH))
				break ;
		}
		parser->info_buf[type][i] = '\0';
		parser->info_buf_flag |= (1<<type);
		parser->info_buf_line[type] = parser->gnl_cnt;
	}
	else
		__add_in_err_buf(parser, ERR_TEXTURE_MULTIDEF);
}

void	__parse_color(t_parser *parser, char *line, int type)
{
	int		i;

	if ((parser->info_buf_flag & (1<<type)) == 0)
	{
		i = 0;
		while (*line && *line != '\n')
		{
			line = __skip_useless_char(line, type, 1);
			while (*line >= '0' && *line <= '9')
				parser->info_buf[type][i++] = *(line++);
			if (*line == ',')
				parser->info_buf[type][i++] = *(line++);
			else if ((*line != '\n' && *line != ' ')
				&& __add_in_err_buf(parser, ERR_FC_COLOR_FORM))
				break ;
		}
		parser->info_buf[type][i] = '\0';
		parser->info_buf_flag |= (1<<type);
		parser->info_buf_line[type] = parser->gnl_cnt;
	}
	else
		__add_in_err_buf(parser, ERR_FC_MULTIDEF);
}

void	__parse_map(t_parser *parser, char *line, int type)
{
	(void) type;
	int	line_len;

	if (parser->map_buf_index < PARSER_BUFFER_SIZE - 1)
	{
		line_len = ft_strlen(line) - 1;
		parser->map_buf[parser->map_buf_index] = line;
		parser->map_line_buf[parser->map_buf_index] = parser->gnl_cnt;
		parser->map_buf_index++;
		if (line_len > parser->map_max_x)
			parser->map_max_x = line_len;
		parser->map_max_y++;
	}
	else
		__add_in_err_buf(parser, ERR_MAP_TOO_BIG);
}

void	__parse_line(t_parser *parser, char *line)
{
	void	((*__parse_line[7])(t_parser *parser, char *line, int type));
	__parse_line[TYPE_NO] = &__parse_texture;
	__parse_line[TYPE_SO] = &__parse_texture;
	__parse_line[TYPE_WE] = &__parse_texture;
	__parse_line[TYPE_EA] = &__parse_texture;
	__parse_line[TYPE_F] = &__parse_color;
	__parse_line[TYPE_C] = &__parse_color;
	__parse_line[TYPE_MAP] = &__parse_map;

	if (parser->type <= TYPE_C)
		line = __skip_useless_char(line, parser->type, 0);
	if (parser->type == TYPE_ERR)
		__add_in_err_buf(parser, ERR_GIBBERISH);
	else
		__parse_line[parser->type](parser, line, parser->type);
	if (parser->type != TYPE_MAP && parser->line)
		free(parser->line);
}
