#include "cub3d.h"

static int	c3d_handle_keypress(int keycode, t_c3d *env)
{
	if (keycode == XK_Escape)
		c3d_exit(env, 0);
	if (keycode == XK_z)
		env->player.pos.y += 1;
	return (0);
}

int	c3d_render_img(t_c3d *env)
{
	c3d_execute_raycasting(env);
	c3d_draw_on_screen(env, &env->mlx);
	return (0);
}

void	c3d_handle_keyhooks(t_c3d *env)
{
	mlx_hook(env->mlx.win_ptr, 2, 1L << 0, &c3d_handle_keypress, env);
	printf("P: %d  \n", env->player.pos.y);
//	mlx_hook(env->mlx.win_ptr, 3, 1L << 1, &c3d_handle_keyrelease, env);
	mlx_hook(env->mlx.win_ptr, 33, 1L << 2, &c3d_exit, env);
	mlx_loop_hook(env->mlx.mlx_ptr, &c3d_render_img, env);
	mlx_loop(env->mlx.mlx_ptr);
}

