/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 03:43:38 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/08/29 14:22:36 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	c3d_exit(t_c3d *env, int errno)
{
	printf("Error: ");
	if (errno == 1)
		printf("1\n");
	if (errno == 2)
		printf("2\n");
	exit(EXIT_SUCCESS);
	return (0);
}
