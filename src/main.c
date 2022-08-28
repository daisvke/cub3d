#include "cub3d.h"

void	c3d_init_window(t_c3d *env, t_mlx *mlx)
{
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->screenw, mlx->screenh, _TITLE);
	if (!mlx->win_ptr)
	{
		free(mlx->win_ptr);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char *argv[])
{
	t_c3d	env;

	c3d_init(&env, argv);
	c3d_init_window(&env, &env.mlx);
	c3d_handle_keyhooks(&env);
	return (0);
}
