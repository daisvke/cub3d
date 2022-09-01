/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 03:43:38 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/09/01 19:41:17 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	c3d_exit(t_c3d *env, int err_code)
{
	(void)	env;

	printf("Error: ");
	if (err_code == 1)
		printf("1\n");
	if (err_code == 2)
		printf("2\n");
	exit(EXIT_SUCCESS);
	return (0);
}



void	c3d_parse_map_exit(t_parser *parser)
{
	int	i;

	i = -1;
	while(++i < parser->map_buf_index)
		free(parser->map_buf[i]);
	exit(EXIT_SUCCESS);
}
