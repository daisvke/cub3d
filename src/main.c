/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 03:43:25 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/09/05 19:47:25 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	c3d_init_window(t_c3d *env, t_mlx *mlx)
{
	mlx->win_ptr = mlx_new_window(\
		mlx->mlx_ptr, mlx->screenw, mlx->screenh, _TITLE);
	if (!mlx->win_ptr)
	{
		c3d_print_err_init(env, 4);
		c3d_exit_game(env, &env->mlx);
	}
}

int	main(int argc, char *argv[])
{
	t_c3d	env;

	(void) argc;
	__c3d_parse_map(&env, argv);
	c3d_init_window(&env, &env.mlx);
	c3d_handle_keyhooks(&env);
	return (0);
}
