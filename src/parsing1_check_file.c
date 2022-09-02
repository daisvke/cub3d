/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:17:13 by lchan             #+#    #+#             */
/*   Updated: 2022/09/02 12:44:28 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	__find_last_c_occurence(char *path, char c)
{
	int	i;
	int	occurence;

	i = -1;
	occurence = i + 1;
	while (path[++i])
		if (path[i] == c)
			occurence = i;
	return (occurence);
}

static int	__check_extention(char *file)
{
	int		dot;
	char	*tmp;
	int		ret;

	ret = 0;
	if (file)
	{
		dot = __find_last_c_occurence(file, '.');
		tmp = file + dot + 1;
		if (dot == 0 || ft_strncmp(tmp, "cub", 4) != 0)
			return (ret | (1<<ERR_EXTENTION));
		return (0);
	}
	return (ret | (1<<ERR_EXTENTION));
}

static int	__check_if_folder(char *file)
{
	int	fd;

	fd = open(file, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return (1<<ERR_FOLDER);
	}
	return (0);
}

/*****************************************************************
 * Set nth bit of integer x to 1 --> x | (1<<n)
 * errno val
 * 		EACCES : cant open file due to accessibility issue
 * 		ENOENT : file does not exist and O_CREAT flag is not set
 * if open syscall fails for other reason, free all and exit;
*****************************************************************/
int	__check_file(char **av, int	*fd, t_parser *parser)
{
	if (*av)
	{
		parser->blocking_err_flag += __check_extention(av[0]);
		parser->blocking_err_flag += __check_if_folder(av[0]);
		*fd = open(av[0], O_RDONLY);
		if (*fd == -1 && !parser->blocking_err_flag)
		{
			if ((errno ^ EACCES) == 0)
				parser->blocking_err_flag |= (1<<ERR_CHMOD);
			else if ((errno ^ ENOENT) == 0)
				parser->blocking_err_flag |= (1<<ERR_PATH);
			else //--> not sure about this one, check with team mate
			{
				perror("cub3d");
				exit(errno);
			}
		}
	}
	else
		parser->blocking_err_flag |= (1<<ERR_NO_FILE);
	return (parser->blocking_err_flag);
}
