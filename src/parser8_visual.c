/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser8_visual.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:43:46 by lchan             #+#    #+#             */
/*   Updated: 2022/09/04 21:06:36 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	__visual_env_rgb(t_c3d *env)
{
	printf("env->floor = %d\n", env->floor.r);
	printf("env->floor = %d\n", env->floor.g);
	printf("env->floor = %d\n", env->floor.b);
	printf("env->ceiling = %d\n", env->ceiling.r);
	printf("env->ceiling = %d\n", env->ceiling.g);
	printf("env->ceiling = %d\n", env->ceiling.b);
}

void	__visual_env_tex_path(t_c3d *env)
{
	printf("env->tex_paths = %s\n", env->tex_paths[0]);
}

void	__visual_env_map(t_c3d *env)
{
	char **tmp;

	tmp = env->map;
	printf(">>>>>> env_map\n");
	while (*tmp)
	{
		printf(" = %s\n", *tmp);
		tmp++;
	}
}

void	__visual_env_player(t_c3d *env)
{
	printf(">>>>>>>player position :\n");
	printf("x = %f\n", env->player.pos.x);
	printf("y = %f\n", env->player.pos.y);
}

void	__visual_env_global(t_c3d *env)
{
	__visual_env_rgb(env);
	__visual_env_tex_path(env);
	__visual_env_map(env);
	__visual_env_player(env);
}
