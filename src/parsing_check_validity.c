/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_validity.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 19:42:12 by lchan             #+#    #+#             */
/*   Updated: 2022/09/01 21:06:45 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	__check_texte_validity(t_parser *parser, char info_buf[6][PATH_MAX + 2])
// {
// 	int			i;
// 	const char	*type_tab[] = {
// 	[TYPE_NO] = "NO", [TYPE_SO] = "SO",
// 	[TYPE_WE] = "WE", [TYPE_EA] = "EA", [TYPE_F] = "F",
// 	[TYPE_C] = "C",
// 	};

// 	i = -1;
// 	while (++i <= TYPE_C)
// 		printf("map_buf[%s] = %s\n", type_tab[i], info_buf[i]);
// }

/*
void	__check_color_validity(t_parser *parser, int type)
{
	int	rgb[3];
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (++j < 3)
	{
		rgb[j] = ft_atoi(parser->info_buf[type] + i);
		if (rgb[j] > 255)
		{

		}
		while (i)
			i++;
		i++;

	}
	i =-1;
	while (parser->info_buf[type][++i])
	{

	}
}
*/


int	__add_to_env(t_parser *parser, t_c3d *env)
{
	(void) env;
	//__check_texte_validity(parser, parser->info_buf);
	//__check_color_validity(parser,);
	//__check_map_validity(parser, parser->map_buf);
	return (parser->blocking_err_flag);
}
