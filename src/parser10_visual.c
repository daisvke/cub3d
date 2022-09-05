/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser10_visual.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:43:46 by lchan             #+#    #+#             */
/*   Updated: 2022/09/05 21:39:51 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	c3d_visual_env_rgb(t_c3d *env)
{
	printf("env->floor = %d\n", env->floor.r);
	printf("env->floor = %d\n", env->floor.g);
	printf("env->floor = %d\n", env->floor.b);
	printf("env->ceiling = %d\n", env->ceiling.r);
	printf("env->ceiling = %d\n", env->ceiling.g);
	printf("env->ceiling = %d\n", env->ceiling.b);
}

void	c3d_visual_env_tex_path(t_c3d *env)
{
	printf("env->tex_paths = %s\n", env->tex_paths[0]);
}

void	c3d_visual_env_map(t_c3d *env)
{
	char	**tmp;

	tmp = env->map;
	printf(">>>>>> env_map\n");
	while (*tmp)
	{
		printf(" = %s\n", *tmp);
		tmp++;
	}
}

void	c3d_visual_env_player(t_c3d *env)
{
	printf(">>>>>>>player position :\n");
	printf("x = %f\n", env->player.pos.x);
	printf("y = %f\n", env->player.pos.y);
}

void	c3d_visual_env_global(t_c3d *env)
{
	c3d_visual_env_rgb(env);
	c3d_visual_env_tex_path(env);
	c3d_visual_env_map(env);
	c3d_visual_env_player(env);
}
