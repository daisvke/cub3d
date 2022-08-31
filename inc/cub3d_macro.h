/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_macro.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:36:58 by lchan             #+#    #+#             */
/*   Updated: 2022/08/31 18:22:02 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_MACRO_H
# define CUB3D_MACRO_H

# define MAP_CHAR " 01SEWN"
# define NBR_PARSING_ERR 11
# define PARSER_BUFFER_SIZE 1024
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
	ERR_NO_FILE,			//bit 0/32
	ERR_EXTENTION,			//bit 1/32
	ERR_FOLDER,				//bit 2/32
	ERR_CHMOD,				//bit 3/32
	ERR_PATH,				//bit 4/32
};

enum	e_map_err{
	ERR_EMPTY_MAP,
	ERR_MISSING_INFO,
	ERR_GIBBERISH,
	/********************	ERR_TEXTURE*/
	ERR_TEXTURE_KEY_MISSING,	//not sure
	ERR_TEXTURE_MULTIDEF,
	ERR_TEXTURE_PATH,
	ERR_TEXTURE_PATH_LENGH,
	/********************	ERR_FC_C*/
	ERR_FC_OVERFLOW,
	ERR_FC_KEY_MISSING,			//not sure
	ERR_FC_MULTIDEF,
	ERR_FC_COLOR_FORM,					//expected color form : F/C 255.255.255
	/********************	ERR_MAP*/
	ERR_MAP_UNVALID_CHAR,
	ERR_MAP_CHARACTER,
	ERR_MAP_BORDERS,
	ERR_MAP_TOO_BIG,					//map has more than 1024 line
};

enum	e_line_type{
	TYPE_NO,
	TYPE_SO,
	TYPE_WE,
	TYPE_EA,
	TYPE_F,
	TYPE_C,
	TYPE_MAP,
	TYPE_ERR,
	TYPE_USELESS,	//line composed of space and/or \n
	TYPE_EOF,		//line start by unvalide char
};

enum	e_cnt_fc{
	FLOOR,
	CELLING,
};
typedef struct s_parser
{
	char	*line;				//current gnl line;
	int		gnl_cnt;
	int		type;				//type of line; e_line_type
	char	*info_buf[6][PATH_MAX + 2];
	char	*map_buf[PARSER_BUFFER_SIZE];
	int		err_buf[PARSER_BUFFER_SIZE];
	int		info_buf_flag;
	int		map_buf_index;		//is also the size of the map
	int		err_buf_index;
	int		err;
}t_parser;



#endif
