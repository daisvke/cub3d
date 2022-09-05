/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 03:43:38 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/09/05 21:40:00 by lchan            ###   ########.fr       */
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
	if (mlx->win_ptr)
	{
		mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	}
	if (mlx->canvas.mlx_img)
		mlx_destroy_image(env->mlx.mlx_ptr, mlx->canvas.mlx_img);
	if (mlx->mlx_ptr)
	{
		mlx_loop_end(mlx->mlx_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		c3d_free(mlx->mlx_ptr);
	}
	exit(EXIT_SUCCESS);
	return (0);
}

void	c3d_parse_map_exit(t_parser *parser)
{
	int	i;

	i = -1;
	while (++i < parser->map_buf_index)
		parser->map_buf[i] = c3d_free(parser->map_buf[i]);
}

void	c3d_add_to_env_exit(t_parser *parser, t_c3d *env)
{
	c3d_parse_map_exit(parser);
	c3d_exit_game(env, &(env->mlx));
}
