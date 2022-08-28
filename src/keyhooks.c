#include "cub3d.h"

int	c3d_handle_keypress(int keycode, t_c3d *env)
{
	if (keycode == XK_Escape)
		c3d_exit(env, 0);
	if (keycode == XK_z || keycode == XK_w)
		env->player.move |= _P1_UP;
	if (keycode == XK_s)
		env->player.move |= _P1_DOWN;
	if (keycode == XK_q || keycode == XK_a)
		env->player.move |= _P1_LEFT;
	if (keycode == XK_d)
		env->player.move |= _P1_RIGHT;
	return (0);
} 

int	c3d_handle_keyrelease(int keycode, t_c3d *env)
{
	if (keycode == XK_z || keycode == XK_w)
		env->player.move &= ~_P1_UP;
	if (keycode == XK_s)
		env->player.move &= ~_P1_DOWN;
	if (keycode == XK_q || keycode == XK_a)
		env->player.move &= ~_P1_LEFT;
	if (keycode == XK_d)
		env->player.move &= ~_P1_RIGHT;
	return (0);
}

void	c3d_render_img(t_c3d *env)
{
//	c3d_check_move(env, env->player);
	c3d_execute_raycasting(env);
	c3d_draw_on_screen(env, &env->mlx);
//	return (0);
}

int	c3d_check_move_and_render(t_c3d *env)
{
	if (env->player.move & _P1_UP)
		env->player.pos.y += env->player.dir.y * _SPEED;
	if (env->player.move & _P1_DOWN)
		env->player.pos.y -= env->player.dir.y * _SPEED;
	if (env->player.move & _P1_LEFT)
		env->player.pos.x -= _SPEED;
	if (env->player.move & _P1_RIGHT)
		env->player.pos.x +=  _SPEED;
	c3d_render_img(env);
	return (0);
}

void	c3d_handle_keyhooks(t_c3d *env)
{
	mlx_hook(env->mlx.win_ptr, 2, 1L << 0, &c3d_handle_keypress, env);
//	printf("P: %f  \n", env->player.pos.y);
	mlx_hook(env->mlx.win_ptr, 3, 1L << 1, &c3d_handle_keyrelease, env);
	mlx_hook(env->mlx.win_ptr, 33, 1L << 2, &c3d_exit, env);
	mlx_loop_hook(env->mlx.mlx_ptr, &c3d_check_move_and_render, env);
	mlx_loop(env->mlx.mlx_ptr);
}
