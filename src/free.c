/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 21:14:04 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/09/02 21:34:18 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
void	c3d_free_tex_paths(t_c3d *env)
{
	int	i;

	i = -1;
	while (++i < _TEX_NBR)
	{
		free(env->textures[i]);
		env->textures[i] = NULL;
	}
}
*/
void	*c3d_free(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

void	c3d_free_array_of_char_pointers(char *array[])
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		c3d_free(array[i]);
		++i;
	}
	array = c3d_free(array);
}

void	c3d_free_array_of_int_pointers(int *array[])
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		c3d_free(array[i]);
		++i;
	}
	array = c3d_free(array);
}

void	c3d_free_pointers_from_char_array(char *array[])
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		c3d_free(array[i]);
		++i;
	}
}

void	c3d_free_pointers_from_int_array(int *array[])
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		c3d_free(array[i]);
		++i;
	}
}
