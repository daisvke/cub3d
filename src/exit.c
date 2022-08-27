#include "cub3d.h"

void	c3d_exit(t_c3d *env, int errno)
{
	printf("Error: ");
	if (errno == 1)
		printf("1\n");
	if (errno == 2)
		printf("2\n");
}
