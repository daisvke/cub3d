/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:48:39 by lchan             #+#    #+#             */
/*   Updated: 2022/08/29 17:43:31 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	__parse_texture(int	*ret)
{

}

void	__parse_fc(int *ret, t_color *floor, t_color *ceiling)
{
	return (ret);

}

void	__parse_map(int *ret, t_c3d *env)
{

}

int	__check_map(t_c3d *env, t_player *player, int fd)
{
	int		ret;
	char	*gnl;

	ret = 0;
	gnl = NULL;
	if (fd > -1)
	{
		ret = 0;
		while (1)
		{
			__parse_texture(&ret);
			__parse_fc(&ret, );
			__parse_map(&ret, t_c3d *env);
		}
		close (fd);
	}
	return (ret);
}
