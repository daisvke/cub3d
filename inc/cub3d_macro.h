/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_macro.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:36:58 by lchan             #+#    #+#             */
/*   Updated: 2022/08/30 19:36:38 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_MACRO_H
# define CUB3D_MACRO_H

# define MAP_CHAR " 01SEWN"
# define NBR_PARSING_ERR 11
# define MESS_ERR_LST "list of errors: \n"

# define MESS_NO_FILE "path to map is missing\n"
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


enum	e_file_err
{
	/********************	ERR_FILE*/
	ERR_NO_FILE,		//bit 0/32
	ERR_EXTENTION,		//bit 1/32
	ERR_FOLDER,			//bit 2/32
	ERR_CHMOD,			//bit 3/32
	ERR_PATH,			//bit 4/32
};

enum	e_map_err{
	ERR_EMPTY_MAP,
	ERR_MISSING_INFO,
	/********************	ERR_TEXTURE*/
	ERR_TEXTURE_KEY,
	ERR_TEXTURE_MULTIDEF,
	ERR_TEXTURE_PATH,
	/********************	ERR_FC_C*/
	ERR_FC_COLOR,
	ERR_FC_KEY,
	ERR_FC_MULTIDEF,
	ERR_FC_LENGH,//??
	/********************	ERR_MAP*/
	ERR_MAP_UNVALID_CHAR,
	ERR_MAP_CHARACTER,
	ERR_MAP_BORDERS,
};

enum	e_line_type{
	TYPE_USELESS = 1,		//line composed of space and/or \n
	TYPE_TEXTURE,
	TYPE_COLOR,
	TYPE_MAP,
	TYPE_ERR,			//line start by unvalide char
	TYPE_EOF,
};

enum	e_cnt_texture{
	E_NO,
	E_SO,
	E_WE,
	E_EA,
	E_F,
	E_C,
	E_MAP,
};

enum	e_cnt_fc{
	FLOOR,
	CELLING,
};
typedef struct s_parser
{
	int		err;
	int		texture_cnt;		//needs to reach 4
	int		fc_cnt;				//needs to reach 2
	int		map_size;			//size of the map
	char	*texture_buffer[4];
	char	*fc_buffer[2];
	char	*map_buffer[1024];
	char	*line;				//current gnl line;
	int		type;				//type of line; e_line_type
}t_parser;

int	__strncmp(const char *s1, const char *s2, size_t n);

#endif
