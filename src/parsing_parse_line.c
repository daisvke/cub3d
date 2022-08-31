/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_parse_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:15:55 by lchan             #+#    #+#             */
/*   Updated: 2022/08/31 18:35:25 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
int	__parse_texture(t_parser *parser, char *line)
{
	int		i;

	if (!(parser->info_buf_flag & (1<<parser->type)))
	{
		i = -1;
		line += 3;
		while (*line == ' ')
			line++;
		while (line[++i] && ft_strchr_b(" \n", line[i]) == 0)
		{
			parser->info_buf[parser->type][i] = line[i];
			if (i == PATH_MAX)
			{
				parser->err |= (1<<ERR_TEXTURE_PATH_LENGH);
				break ;
			}
		}
		parser->info_buf[parser->type][i] = '\0';
		parser->info_buf_flag |= (1<<parser->type);
		free(parser->line);
	}
	parser->err |= (1<<ERR_TEXTURE_MULTIDEF);
}

int	__parse_color(t_parser *parser, char *line)
{
	char	buffer[PATH_MAX + 2];
	int		i;

	line += 2;
	while (*line && *line != '\n')
	{
		while (*line == ' ')
			line++;
		while (*line >= '0' && *line <= '9')
			*(line++) = buffer[i++];
		if (* line = ',' && i <= PATH_MAX)
			*(line++) = buffer[i++];
		else
		{
			parser->err |= (1<<ERR_FC_COLOR_FORM);
			break ;
		}
	}
	buffer[i] = '\0';
}

int	__parse_map(t_parser *parser, char *line)
{
	if (parser->map_buf_index < PARSER_BUFFER_SIZE - 1)
	{
		parser->map_buf[parser->map_buf_index] = line;
		parser->map_buf_index++;
	}
	else
		parser->err |= (1<<ERR_MAP_TOO_BIG);
}

int	__parse_err(t_parser *parser, char *line)
{
	if (parser->err_buf_index < PARSER_BUFFER_SIZE)
	{
		parser->err_buf[parser->err_buf_index] = parser->gnl_cnt;
		parser->err_buf_index++;
	}
	parser->err |= (1<<ERR_GIBBERISH);
}
*/
void	__parse_line(t_parser *parser, char *line)
{
	/*int	((*__parse_line[7])(t_parser *parser, char *line)); //not sure it's gonna be an int
	__parse_line[TYPE_NO] = &__parse_texture;
	__parse_line[TYPE_SO] = &__parse_texture;
	__parse_line[TYPE_WE] = &__parse_texture;
	__parse_line[TYPE_EA] = &__parse_texture;
	__parse_line[TYPE_F] = &__parse_color;
	__parse_line[TYPE_C] = &__parse_color;
	__parse_line[TYPE_MAP] = &__parse_map;
	__parse_line[TYPE_ERR] = &__parse_err;

	__parse_line[parser->type](parser, parser->line);*/
	printf("type = %d\n", parser->type);
	printf("line = %s\n", parser->line);
}
