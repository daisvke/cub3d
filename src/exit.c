/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 03:43:38 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/09/02 21:37:49 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	c3d_exit_game(t_c3d *env, t_mlx *mlx)
{
	if (env->map)
		c3d_free_array_of_char_pointers(env->map);
	if (env->buffer)
		c3d_free_array_of_int_pointers(env->buffer);
	c3d_free_pointers_from_int_array(env->textures);
	c3d_free_pointers_from_char_array(env->tex_paths);
	if (mlx->win_ptr)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	if (mlx->canvas.mlx_img)
		mlx_destroy_image(env->mlx.mlx_ptr, mlx->canvas.mlx_img);
	if (mlx->mlx_ptr)
	{
		mlx_loop_end(mlx->mlx_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		c3d_free(mlx->mlx_ptr);
	}
	exit(EXIT_SUCCESS);
}

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
