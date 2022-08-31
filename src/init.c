/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 03:43:21 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/09/01 00:44:33 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	c3d_convert_rgb_to_int(t_color color)
{
	int	val;

	val = color.r;
	val = (val << 8) + color.g;
	val = (val << 8) + color.b;
	return (val);
}

void	c3d_init_mlx(t_c3d *env, t_mlx *mlx)
{
	int	w;
	int	h;

	mlx->screenw = _SCREENW;
	mlx->screenh = _SCREENH;
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		c3d_exit(env, 1);
	mlx_get_screen_size(mlx->mlx_ptr, &w, &h);
	if (w < mlx->screenw)
		mlx->screenw = w;
	if (h < mlx->screenh)
		mlx->screenh = h;
	if (mlx->screenw <= 0 || mlx->screenh <= 0)
		c3d_exit(env, 2);
	mlx->canvas.mlx_img = mlx_new_image(mlx->mlx_ptr, mlx->screenw, \
		mlx->screenh);
	mlx->canvas.addr = (int *)mlx_get_data_addr(mlx->canvas.mlx_img, \
		&mlx->canvas.bpp, &mlx->canvas.line_len, &mlx->canvas.endian);
	c3d_init_window(env, mlx);
}

void	c3d_parse_map(t_c3d *env, t_player *player, char *argv[])
{
	(void) argv;
	// F and C from map
	env->floor.r = 2;
	env->floor.g = 2;
	env->floor.b = 252;
	env->floor.color = c3d_convert_rgb_to_int(env->floor);
	env->ceiling.r = 200;
	env->ceiling.g = 20;
	env->ceiling.b = 200;
	env->ceiling.color = c3d_convert_rgb_to_int(env->ceiling);
	// initial pos of the player, depends on where NSEW is set on the map
	player->pos.x = 10;
	player->pos.y = 5;
	// initial direction where player is looking at
	// below corresponds to north (N)
	player->dir.x = 0;
	player->dir.y = -1;
	// texture paths
	env->tex_paths[0] = "./img/no_wall.xpm";
	env->tex_paths[1] = "./img/so_wall.xpm";
	env->tex_paths[2] = "./img/we_wall.xpm";
	env->tex_paths[3] = "./img/ea_wall.xpm";

	char map[7][21] = {
		"111111111111111111111",
		"100000000110000000011",
		"100000010000010000001",
		"101000000000010010001",
		"100000000000110000001",
		"1000000000N0000000001",
		"111111111111111111111"
	};
	env->map = malloc(sizeof(*env->map) * 8);
	env->map[7] = 0;
	for (int i=0; i < 7; ++i)
	{
		env->map[i] = malloc(sizeof(char) * 22);
		env->map[i][21] = 0;
	}
	for (int i=0; i < 7; ++i)
		for (int j=0; j < 21; ++j)
			env->map[i][j] = map[i][j];
}

void	c3d_init_buffers(t_c3d *env, t_mlx mlx) //buffer?
{
	double	w;

	w = mlx.screenw;
//	env->zbuffer = malloc(sizeof(double) * w);
	env->buffer = malloc(sizeof(*env->buffer) * (mlx.screenh + 1));
	env->buffer[mlx.screenh] = 0;
	for (int i=0; i < mlx.screenh; ++i)
	{
		env->buffer[i] = malloc(sizeof(**env->buffer) * (mlx.screenw + 1));
		env->buffer[i][mlx.screenw] = 0;
	}
}

void	c3d_init_texture_array(t_c3d *env)
{
	int	i;

//	env->textures = malloc(sizeof(*env->textures) * _TEX_NBR);
	i = 0;
	while (i < _TEX_NBR)
	{
		env->textures[i] = malloc(sizeof(**env->textures) * _TEX_SIZE * _TEX_SIZE);
		++i;
	}
}

void	c3d_load_texture(t_c3d *env, t_mlx *mlx, int *tex, char *path)
{
	int		x;
	int		y;
	t_img	img;

	img.mlx_img = mlx_xpm_file_to_image(mlx->mlx_ptr, path, &img.x, &img.y);
	if (!img.mlx_img)
		printf("ERROR MLX IMG\n");
	img.addr = (int *)mlx_get_data_addr(img.mlx_img, &img.bpp, &img.line_len, &img.endian);
	y = 0;
	while (y < img.y)
	{
		x = 0;
		while (x < img.x)
		{
			tex[img.x * y + x] = img.addr[img.x * y + x];
			++x;
		}
		++y;
	}
	mlx_destroy_image(mlx->mlx_ptr, img.mlx_img);
}

void	c3d_load_textures(t_c3d *env, t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < _TEX_NBR)
	{
		c3d_load_texture(env, mlx, env->textures[i], env->tex_paths[i]);
		++i;
	}
}

void	c3d_init_player_settings(t_mlx mlx, t_player *player)
{
	player->cam_plane.x = 0.66;
	player->cam_plane.y = 0.0;
	player->speed = (_SPEED * (mlx.screenw * mlx.screenh)) / (680 * 460);
}

void	c3d_init(t_c3d *env, char *argv[])
{
	c3d_memset(env, 0, sizeof(t_c3d));
	c3d_parse_map(env, &env->player, argv);
	c3d_init_mlx(env, &env->mlx);
	c3d_init_buffers(env, env->mlx);
	c3d_init_texture_array(env);
	c3d_load_textures(env, &env->mlx);
	c3d_init_player_settings(env->mlx, &env->player);
}
