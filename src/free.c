/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 21:14:04 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/09/04 16:47:08 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	while (array[i] && i < _TEX_NBR)
	{
		c3d_free(array[i]);
		++i;
	}
}

void	c3d_free_pointers_from_int_array(int *array[])
{
	size_t	i;

	i = 0;
	while (array[i] && i < _TEX_NBR)
	{
		c3d_free(array[i]);
		++i;
	}
}
