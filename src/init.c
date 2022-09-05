/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 03:43:21 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/09/05 19:50:34 by lchan            ###   ########.fr       */
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
		env->textures[i] = malloc(sizeof(**env->textures) * _TEX_SIZE * _TEX_SIZE);
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
	int	((*c3d_init[4])(t_c3d *env,  t_mlx *mlx));
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
	env->player.speed =
	(_SPEED * (env->mlx.screenw * env->mlx.screenh)) / (680 * 460);
	return (ret);
}


/******************* OLD VERSION ***********************/

// /*
// void	c3d_init_window(t_c3d *env, t_mlx *mlx)
// {
// 	mlx->win_ptr = mlx_new_window(\
// 		mlx->mlx_ptr, mlx->screenw, mlx->screenh, _TITLE);
// 	if (!mlx->win_ptr)
// 		c3d_print_err_init(env, 4);//free etc
// }
// */
// void	c3d_init_mlx(t_c3d *env, t_mlx *mlx)
// {
// 	int	w;
// 	int	h;

// 	mlx->screenw = _SCREENW;
// 	mlx->screenh = _SCREENH;
// 	mlx->mlx_ptr = mlx_init();
// 	if (!mlx->mlx_ptr)
// 		c3d_print_err_init(env, 1);
// 	mlx_get_screen_size(mlx->mlx_ptr, &w, &h);
// 	if (w < mlx->screenw)
// 		mlx->screenw = w;
// 	if (h < mlx->screenh)
// 		mlx->screenh = h;
// 	if (mlx->screenw <= 0 || mlx->screenh <= 0)
// 		c3d_print_err_init(env, 2);
// 	mlx->canvas.mlx_img = mlx_new_image(mlx->mlx_ptr, mlx->screenw, \
// 		mlx->screenh);
// 	if (!mlx->canvas.mlx_img)
// 		c3d_print_err_init(env, 3);
// 	mlx->canvas.addr = (int *)mlx_get_data_addr(mlx->canvas.mlx_img, \
// 		&mlx->canvas.bpp, &mlx->canvas.line_len, &mlx->canvas.endian);
// 	//c3d_init_window(env, mlx);
// }

// // int	c3d_convert_rgb_to_int(t_color color)
// // {
// // 	int	val;

// // 	val = color.r;
// // 	val = (val << 8) + color.g;
// // 	val = (val << 8) + color.b;
// // 	return (val);
// // }

// // void	c3d_parse_map(t_c3d *env, t_player *player, char *argv[])
// // {
// // 	(void)argv;
// // 	// F and C from map
// // 	// env->floor.r = 70;
// // 	// env->floor.g = 70;
// // 	// env->floor.b = 70;
// // 	// env->floor.color = c3d_convert_rgb_to_int(env->floor);
// // 	// env->ceiling.r = 38;
// // 	// env->ceiling.g = 38;
// // 	// env->ceiling.b = 38;
// // 	// env->ceiling.color = c3d_convert_rgb_to_int(env->ceiling);

// // 	// initial pos of the player, depends on where NSEW is set on the map




// // 	// player->pos.x = 11;
// // 	// player->pos.y = 5;

// // 	// initial direction where player is looking at
// // 	char orient = 'N';
// // 	if (orient == 'N')
// // 	{
// // 		player->dir.x = 0.0;
// // 		player->dir.y = -1.0;
// // 		player->cam_plane.x = 0.66;
// // 		player->cam_plane.y = 0.0;
// // 	}
// // 	else if (orient == 'S')
// // 	{
// // 		player->dir.x = 0.0;
// // 		player->dir.y = 1.0;
// // 		player->cam_plane.x = -0.66;
// // 		player->cam_plane.y = 0.0;
// // 	}
// // 	else if (orient == 'W')
// // 	{
// // 		player->dir.x = -1.0;
// // 		player->dir.y = 0.0;
// // 		player->cam_plane.x = 0.0;
// // 		player->cam_plane.y = -0.66;
// // 	}
// // 	else if (orient == 'E')
// // 	{
// // 		player->dir.x = 1.0;
// // 		player->dir.y = 0.0;
// // 		player->cam_plane.x = 0.0;
// // 		player->cam_plane.y = 0.66;
// // 	}



// // 	// texture paths
// // 	// env->tex_paths[0] = "./img/no_wall.xpm";
// // 	// env->tex_paths[1] = "./img/so_wall.xpm";
// // 	// env->tex_paths[2] = "./img/we_wall.xpm";
// // 	// env->tex_paths[3] = "./img/ea_wall.xpm";

// // 	// char map[7][21] = {
// // 	// 	"111111111111111111111",
// // 	// 	"100000000110000000011",
// // 	// 	"100000010000010000001",
// // 	// 	"101000000000010010001",
// // 	// 	"100000000000110000001",
// // 	// 	"1000000000N0000000001",
// // 	// 	"111111111111111111111"
// // 	// };
// // 	// env->map = malloc(sizeof(*env->map) * 8);
// // 	// env->map[7] = 0;
// // 	// for (int i=0; i < 7; ++i)
// // 	// {
// // 	// 	env->map[i] = malloc(sizeof(char) * 22);
// // 	// 	env->map[i][21] = 0;
// // 	// }
// // 	// for (int i=0; i < 7; ++i)
// // 	// {
// // 	// 	for (int j=0; j < 21; ++j)
// // 	// 	{
// // 	// 		if (ft_strchr_b(MAP_ORIENT_CHAR, map[i][j]) != FOUND)
// // 	// 			env->map[i][j] = map[i][j];
// // 	// 		else
// // 	// 			env->map[i][j] = '0';
// // 	// 		if (j == 20)
// // 	// 			env->map[i][j + 1] = 0;
// // 	// 	}
// // 	// }
// // }

// void	c3d_init_buffer(t_c3d *env, t_mlx mlx)
// {
// 	int	h;
// 	int	w;

// 	h = mlx.screenh;
// 	w = mlx.screenw;
// 	env->buffer = malloc(sizeof(*env->buffer) * (h + 1));
// 	env->buffer[h] = 0;
// 	for (int i=0; i < h; ++i)
// 	{
// 		env->buffer[i] = malloc(sizeof(**env->buffer) * (w + 1));
// 		env->buffer[i][w] = 0;
// 	}
// }

// void	c3d_init_texture_array(t_c3d *env)
// {
// 	int	i;

// 	i = 0;
// 	while (i < _TEX_NBR)
// 	{
// 		env->textures[i] = malloc(sizeof(**env->textures) * _TEX_SIZE * _TEX_SIZE);
// 		++i;
// 	}
// }

// // void	c3d_load_texture(t_c3d *env, t_mlx *mlx, int *tex, char *path)
// // {
// // 	int		x;
// // 	int		y;
// // 	t_img	img;

// // 	img.mlx_img = mlx_xpm_file_to_image(mlx->mlx_ptr, path, &img.x, &img.y);
// // 	if (!img.mlx_img)
// // 		printf("ERROR MLX IMG\n");
// // 	img.addr = (int *)mlx_get_data_addr(img.mlx_img, &img.bpp, &img.line_len, &img.endian);
// // 	y = 0;
// // 	while (y < img.y)
// // 	{
// // 		x = 0;
// // 		while (x < img.x)
// // 		{
// // 			tex[img.x * y + x] = img.addr[img.x * y + x];
// // 			++x;
// // 		}
// // 		++y;
// // 	}
// // 	mlx_destroy_image(mlx->mlx_ptr, img.mlx_img);
// // }

// // void	c3d_load_textures(t_c3d *env, t_mlx *mlx)
// // {
// // 	int	i;

// // 	i = 0;
// // 	while (i < _TEX_NBR)
// // 	{
// // 		c3d_load_texture(env, mlx, env->textures[i], env->tex_paths[i]);
// // 		++i;
// // 	}
// // }

// void	c3d_init_player_settings(t_mlx mlx, t_player *player)
// {
// 	player->speed = (_SPEED * (mlx.screenw * mlx.screenh)) / (680 * 460);
// }

// void	c3d_init(t_c3d *env)
// {
// 	c3d_memset(env, 0, sizeof(t_c3d));
// 	//c3d_parse_map(env, &env->player, argv);
// 	c3d_init_mlx(env, &env->mlx);
// 	c3d_init_buffer(env, env->mlx);
// 	c3d_init_texture_array(env);
// 	//c3d_load_textures(env, &env->mlx);
// 	c3d_init_player_settings(env->mlx, &env->player);
// }

