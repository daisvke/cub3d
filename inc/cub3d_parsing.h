/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parsing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:36:58 by lchan             #+#    #+#             */
/*   Updated: 2022/08/29 14:41:27 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PARSING_H
# define CUB3D_PARSING_H

# include "cub3d.h"

# define NBR_PARSING_ERR 10
enum	e_parse_err
{
	/********************	ERR_FILE*/
	ERR_EXTENTION,	//bit 0/32
	ERR_FOLDER,		//bit 1/32
	ERR_CHMOD,		//bit 2/32
	ERR_PATH,		//bit 3/32
	/********************	ERR_TEXTURE*/
	ERR_TEXTURE_KEY,
	ERR_TEXTURE_PATH,
	/********************	ERR_FC*/
	ERR_FC_COLOR,
	ERR_FC_KEY,
	ERR_FC_LENGH,
	/********************	ERR_MAP*/
	ERR_MAP_LENGH,
	ERR_MAP_CHAR,
	ERR_MAP_BORDERS,
};

void	__c3d_parse_map(t_c3d *env, t_player *player, char **argv);
int		_check_file(char **av, int	*fd);

#endif
