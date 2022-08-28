#include "cub3d.h"

int	c3d_handle_keypress(int keycode, t_c3d *env)
{
	if (keycode == XK_Escape)
		c3d_exit(env, 0);
	if (keycode == XK_Left)
		env->player.move |= _CAM_LEFT;
	if (keycode == XK_Right)
		env->player.move |= _CAM_RIGHT;
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
	if (keycode == XK_Left)
		env->player.move &= ~_CAM_LEFT;
	if (keycode == XK_Right)
		env->player.move &= ~_CAM_RIGHT;
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

void	c3d_render_and_put_img_to_window(t_c3d *env)
{
	c3d_execute_raycasting(env);
	c3d_draw_on_screen(env, &env->mlx);
}

int	c3d_move_and_render(t_c3d *env)
{
	if (env->player.move & _P1_UP)
		c3d_check_obstacles_and_move_up(env->map, &env->player);
	if (env->player.move & _P1_DOWN)
		c3d_check_obstacles_and_move_down(env->map, &env->player);
	if (env->player.move & _P1_LEFT)
		c3d_check_obstacles_and_move_left(env->map, &env->player);
	if (env->player.move & _P1_RIGHT)
		c3d_check_obstacles_and_move_right(env->map, &env->player);
	if (env->player.move & _CAM_LEFT)
		c3d_look_left(&env->player);
	if (env->player.move & _CAM_RIGHT)
		c3d_look_right(&env->player);
	c3d_render_and_put_img_to_window(env);
	return (0);
}

void	c3d_handle_keyhooks(t_c3d *env)
{
	mlx_hook(env->mlx.win_ptr, 2, 1L << 0, &c3d_handle_keypress, env);
	mlx_hook(env->mlx.win_ptr, 3, 1L << 1, &c3d_handle_keyrelease, env);
	mlx_hook(env->mlx.win_ptr, 33, 1L << 2, &c3d_exit, env);
	mlx_loop_hook(env->mlx.mlx_ptr, &c3d_move_and_render, env);
	mlx_loop(env->mlx.mlx_ptr);
}
