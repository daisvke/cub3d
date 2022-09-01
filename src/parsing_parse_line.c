/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_parse_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:15:55 by lchan             #+#    #+#             */
/*   Updated: 2022/09/01 21:12:41 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		if (parser->line)
			free(parser->line);
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
			while (*line == ' ')
				line++;
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
	if (parser->line)
		free(parser->line);
}

void	__parse_map(t_parser *parser, char *line, int type)
{
	(void) type;
	if (parser->map_buf_index < PARSER_BUFFER_SIZE - 1)
	{
		parser->map_buf[parser->map_buf_index] = line;
		parser->map_line_buf[parser->map_buf_index] = parser->gnl_cnt;
		parser->map_buf_index++;
	}
	else
		__add_in_err_buf(parser, ERR_MAP_TOO_BIG);
}

char	*__skip_useless_char(char *line, int type)
{
	while (*line == ' ')
		line++;
	if (type <= TYPE_EA)
		line += 3;
	else
		line += 2;
	while (*line == ' ')
		line++;
	return (line);
}

void	__parse_line(t_parser *parser, char *line)
{
	void	((*__parse_line[8])(t_parser *parser, char *line, int type)); //not sure it's gonna be an int
	__parse_line[TYPE_NO] = &__parse_texture;
	__parse_line[TYPE_SO] = &__parse_texture;
	__parse_line[TYPE_WE] = &__parse_texture;
	__parse_line[TYPE_EA] = &__parse_texture;
	__parse_line[TYPE_F] = &__parse_color;
	__parse_line[TYPE_C] = &__parse_color;
	__parse_line[TYPE_MAP] = &__parse_map;

	if (parser->type <= TYPE_C)
		line = __skip_useless_char(line, parser->type);
	if (parser->type == TYPE_ERR)
		__add_in_err_buf(parser, ERR_GIBBERISH);
	else
		__parse_line[parser->type](parser, line, parser->type);
}
