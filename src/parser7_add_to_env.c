/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser7_add_to_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:05:25 by lchan             #+#    #+#             */
/*   Updated: 2022/09/03 17:14:48 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	c3d_add_map_to_env(t_parser *parser, t_c3d *env)
{
	(void) parser;
	(void) env;
	printf("max_x = %d\n", parser->map_max_x);
	printf("max_y = %d\n", parser->map_max_y);
	return 0;
}
