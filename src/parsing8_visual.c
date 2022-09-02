/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing8_visual.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:43:46 by lchan             #+#    #+#             */
/*   Updated: 2022/09/02 16:52:49 by lchan            ###   ########.fr       */
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
