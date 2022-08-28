#include "cub3d.h"

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
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, w, h, _TITLE);
	if (!mlx->win_ptr)
	{
		free(mlx->win_ptr);
		exit(EXIT_FAILURE);
	}
	mlx->canvas.mlx_img = mlx_new_image(mlx->mlx_ptr, mlx->screenw, \
		mlx->screenh);
	mlx->canvas.addr = (int *)mlx_get_data_addr(mlx->canvas.mlx_img, \
		&mlx->canvas.bpp, &mlx->canvas.line_len, &mlx->canvas.endian);
}

void	c3d_parse_map(t_c3d *env, t_player *player, char *argv[])
{
	player->pos.x = 3;
	player->pos.y = 3;
	char map[7][21] = {
		"111111111111111111111",
		"100000000000000000001",
		"100000011100000000001",
		"100000111110000000001",
		"100000000000000000001",
		"10000000N000000000001",
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

void	c3d_init_buffers(t_c3d *env, t_mlx mlx)
{
	double	w;

	w = mlx.screenw;
	env->zbuffer = malloc(sizeof(double) * w);
	env->buffer = malloc(sizeof(*env->buffer) * (mlx.screenh + 1));
	env->buffer[mlx.screenh] = 0;
	for (int i=0; i < mlx.screenh; ++i)
	{
		env->buffer[i] = malloc(sizeof(**env->buffer) * (mlx.screenw + 1));
		env->buffer[i][mlx.screenw] = 0;
	}
//	ft_memset(env->buffer, 0, sizeof(env->buffer));
}

void	c3d_init(t_c3d *env, char *argv[])
{
	ft_memset(env, 0, sizeof(t_c3d));
	c3d_parse_map(env, &env->player, argv);
	c3d_init_mlx(env, &env->mlx);
	c3d_init_buffers(env, env->mlx);
}
