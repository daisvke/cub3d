#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_c3d	env;

	c3d_init(&env, argv);
	while (1)
	{
		c3d_execute_raycasting(&env);
		c3d_draw_on_screen(&env, &env.mlx);
	}
	return (0);
}
