/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_macro.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:36:58 by lchan             #+#    #+#             */
/*   Updated: 2022/08/29 17:59:04 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_MACRO_H
# define CUB3D_MACRO_H

# define OK_CHAR " 01SEWN"
# define NBR_PARSING_ERR 11
# define MESS_ERR_LST "list of errors: \n"
# define MESS_NO_FILE "file is missing\n"
# define MESS_EXTENTION "invalid extention\n"
# define MESS_FOLDER "expecting : file.cut but received : directory.cub\n"
# define MESS_CHMOD "access denied\n"
# define MESS_PATH "path seems incorrect\n"
//# define MESS_TEXTURE_KEY "unvalid extention\n"
//# define MESS_TEXTURE_PATH "unvalid extention\n"
//# define MESS_FC_COLOR "unvalid extention\n"
//# define MESS_FC_KEY "unvalid extention\n"
//# define MESS_FC_LENGH "unvalid extention\n"
//# define MESS_MAP_LENGH "unvalid extention\n"
//# define MESS_MAP_CHAR "unvalid extention\n"
//# define MESS_MAP_BORDERS "unvalid extention\n"
//# define MESS_MAP_BORDERS "unvalid extention\n"


enum	e_parse_err
{
	/********************	ERR_FILE*/
	ERR_NO_FILE,		//bit 0/32
	ERR_EXTENTION,		//bit 1/32
	ERR_FOLDER,			//bit 2/32
	ERR_CHMOD,			//bit 3/32
	ERR_PATH,			//bit 4/32
	/********************	ERR_TEXTURE*/
	ERR_TEXTURE_KEY,
	ERR_TEXTURE_PATH,
	/********************	ERR_FC_C*/
	ERR_FC_COLOR,
	ERR_FC_KEY,
	ERR_FC_LENGH,
	/********************	ERR_MAP*/
	ERR_MAP_UNVALID_CHAR,
	ERR_MAP_CHARACTER,
	ERR_MAP_BORDERS,
};

#endif
