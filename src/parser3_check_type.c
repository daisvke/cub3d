/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pick_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 11:37:37 by lchan             #+#    #+#             */
/*   Updated: 2022/08/31 15:12:56 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	__is_type_null(char *line, int *type)
{
	if (!line)
	{
		*type = TYPE_EOF;
		return (1);
	}
	return (0);
}

static int	__is_type_useless(char *line, int *type)
{
	if (*line == '\n')
	{
		*type = TYPE_USELESS;
		return (1);
	}
	return (0);
}

/**************************************************************
 * based on where type stops, the corresponding e_line_type will be returned
 * ************************************************************/
static int	__is_type_key(char *line, int *type)
{
	const char	*key_tab[] = {
	[TYPE_NO] = "NO ", [TYPE_SO] = "SO ",
	[TYPE_WE] = "WE ", [TYPE_EA] = "EA ",
	[TYPE_F] = "F ", [TYPE_C] = "C ",
	};

	while ((*type) < TYPE_MAP)
	{
		if (ft_strncmp(key_tab[*type], line,
			ft_strlen((char *)key_tab[*type])) == 0)
			return (1) ;
		(*type)++;
	}
	return (0);
}

static int	__is_type_map(char *line, int *type)
{
	while (*line != '\n')
	{
		if (ft_strchr_b(MAP_CHAR, *line) == -1)
		{
			*type = TYPE_ERR;
			break ;
		}
		line++;
	}
	if (*type != TYPE_ERR)
		*type = TYPE_MAP;
	return (*type);
}

int	__check_type(char *line, int *type)
{
	int	i;
	int	((*__check_type[4])(char *line, int *type));

	__check_type[0] = &__is_type_null;
	__check_type[1] = &__is_type_useless;
	__check_type[2] = &__is_type_key;
	__check_type[3] = &__is_type_map;
	i = 0;
	*type = 0;
	if (line)
		while (*line == ' ')
			line++;
	while (i < 4)
		if (__check_type[i++](line, type))
			break ;
	return (*type);
}
