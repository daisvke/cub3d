/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 03:43:21 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/09/05 23:00:35 by mint             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	c3d_init_mlx(t_c3d *env, t_mlx *mlx)
{
	int	w;
	int	h;

	(void) env;
	mlx->screenw = _SCREENW;
	mlx->screenh = _SCREENH;
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (1);
	mlx_get_screen_size(mlx->mlx_ptr, &w, &h);
	if (w < mlx->screenw)
		mlx->screenw = w;
	if (h < mlx->screenh)
		mlx->screenh = h;
	if (mlx->screenw <= 0 || mlx->screenh <= 0)
		return (2);
	mlx->canvas.mlx_img = mlx_new_image(mlx->mlx_ptr, mlx->screenw, \
		mlx->screenh);
	if (!mlx->canvas.mlx_img)
		return (3);
	mlx->canvas.addr = (int *)mlx_get_data_addr(mlx->canvas.mlx_img, \
		&mlx->canvas.bpp, &mlx->canvas.line_len, &mlx->canvas.endian);
	return (0);
}

int	c3d_init_buffer(t_c3d *env, t_mlx *mlx)
{
	int	h;
	int	w;
	int	i;

	h = mlx->screenh;
	w = mlx->screenw;
	i = -1;
	env->buffer = malloc(sizeof(*env->buffer) * (h + 1));
	if (!env->buffer)
		return (-1);
	env->buffer[h] = 0;
	while (++i < h)
	{
		env->buffer[i] = malloc(sizeof(**env->buffer) * (w + 1));
		if (!env->buffer[i])
			return (-1);
		env->buffer[i][w] = 0;
	}
	return (0);
}

int	c3d_init_texture_array(t_c3d *env, t_mlx *mlx)
{
	int	i;

	(void) mlx;
	i = 0;
	while (i < _TEX_NBR)
	{
		env->textures[i] = \
		malloc(sizeof(**env->textures) * _TEX_SIZE * _TEX_SIZE);
		if (!env->textures[i])
			return (-1);
		++i;
	}
	return (0);
}

int	c3d_print_err_init(t_c3d *env, int err_code)
{
	(void) env;
	__putstr_err(NULL, "Error code: ");
	if (err_code == -1)
		perror("");
	else if (err_code == 1)
		__putstr_err(NULL, MS_MLX_INIT);
	else if (err_code == 2)
		__putstr_err(NULL, MS_MLX_RESOLUTION);
	else if (err_code == 3)
		__putstr_err(NULL, MS_MLX_NEW_IMG);
	else if (err_code == 4)
		__putstr_err(NULL, MS_MLX_NEW_WIN);
	return (err_code);
}

int	c3d_init(t_c3d *env)
{
	int	i;
	int	ret;
	int	((*c3d_init[4])(t_c3d *env, t_mlx *mlx));

	c3d_init[0] = &c3d_init_mlx;
	c3d_init[1] = &c3d_init_buffer;
	c3d_init[2] = &c3d_init_texture_array;
	i = -1;
	ret = 0;
	c3d_memset(env, 0, sizeof(t_c3d));
	while (++i < 3)
	{
		ret = c3d_init[i](env, &env->mlx);
		if (ret)
		{
			c3d_print_err_init(env, ret);
			return (ret);
		}
	}
	env->player.speed = \
	(_SPEED * (env->mlx.screenw * env->mlx.screenh)) / (680 * 460);
	return (ret);
}
