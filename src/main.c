/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 03:43:25 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/09/04 22:24:31 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_c3d	env;

	if (argc == 2)
	{
		c3d_init(&env, argv);
		__c3d_parse_map(&env, &(env.player), argv);
		c3d_handle_keyhooks(&env);
	}
	//printf("Error: not enough arguments\n"); // print usage
	return (0);
}
