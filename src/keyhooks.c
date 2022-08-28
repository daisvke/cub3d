#include "cub3d.h"

int	c3d_handle_keypress(int keycode, t_c3d *env)
{
	if (keycode == XK_Escape)
		c3d_exit(env, 0);
	return (0);
}

void	c3d_handle_keyhooks(t_c3d *env)
{
	mlx_hook(env->mlx.win_ptr, 2, 1L << 0, &c3d_handle_keypress, env);
//	mlx_hook(env->mlx.win_ptr, 3, 1L << 1, &c3d_handle_keyrelease, env);
	mlx_hook(env->mlx.win_ptr, 33, 1L << 2, &c3d_exit, env);
//	mlx_loop_hook(env->mlx.mlx_ptr, &cub_move, env);
	mlx_loop(env->mlx.mlx_ptr);
}

