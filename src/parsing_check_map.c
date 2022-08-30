/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:48:39 by lchan             #+#    #+#             */
/*   Updated: 2022/08/30 21:13:22 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	__check_null(char *line, int *type)
{
	if (!line)
	{
		*type = TYPE_EOF;
		return (*type);
	}
	return (0);
}

int	__check_useless(char *line, int *type)
{
	char	*tmp;

	tmp = line;
	while (*tmp == ' ')
		tmp++;
	if (*tmp == '\n')
	{
		*type = TYPE_USELESS;
		return (*type);
	}
	return (0);
}

int	__check_key(char *line, int *type)
{
	const char	*key_tab[] = {
	[E_NO] = "NO ", [E_NO] = "SO ", [E_WE] = "WE ", [E_EA] = "EA ",
	[E_F] = "F ", [E_C] = "C ", [E_MAP] = MAP_CHAR,
	};
	int			i;
	char		*tmp;

	i = -1;
	tmp = line;
	while (*tmp == ' ')
		tmp++;
	while (++i < E_MAP)
		if (__strncmp(key_tab[i], line, __strlen(key_tab[i])))
			break ;
	if (i <= E_EA)
		*type = TYPE_TEXTURE;
	else if (i <= E_C)
		*type = TYPE_COLOR;
	else if (i <= E_MAP)
		*type = TYPE_MAP;
	else
		*type = TYPE_ERR;
	return (*type);
}

int	__check_type(char *line, int *type)
{
	int	i;
	int	((*__check_type[3])(char *line, int *type));

	__check_type[0] = &__check_null;
	__check_type[1] = &__check_useless;
	__check_type[2] = &__check_key;
	i = 0;
	while (i < 3)
		if (__check_type[i++](line, type))
			break ;
	return (*type);
}








void	__pick_line(int fd, t_parser *parser)
{
	//char	*map_line;
	//int		line_type;

	parser->line = get_next_line(fd);
	while (__check_line_type(parser->line, &parser->type) == TYPE_USELESS)
	{
		free(parser->line);
		parser->line = get_next_line(fd);
	}
}

int	__check_map(t_c3d *env, t_player *player, int fd)
{
	t_parser	parser;

	ft_memset(&parser, 0, sizeof(t_parser));
	if (fd > -1)
	{
		parser.err |= (1<<ERR_EMPTY_MAP);
		__pick_line(fd, &parser);
		while (parser.line)
		{
			__parse_map_line(&parser);
			__pick_line(fd, &parser);
		}
		close (fd);
		if (__check_info_validity(&parser))
			__add_info_to_env(&parser, env);
	}
	return (parser.err);
}

			// __parse_texture(&ret);
			// __parse_fc(&ret, );
			// __parse_map(&ret, t_c3d *env);
// void	__parse_texture(int	*ret)
// {

// }

// void	__parse_fc(int *ret, t_color *floor, t_color *ceiling)
// {
// 	return (ret);

// }

// void	__parse_map(int *ret, t_c3d *env)
// {

// }
