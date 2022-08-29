/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:17:13 by lchan             #+#    #+#             */
/*   Updated: 2022/08/29 15:00:24 by lchan            ###   ########.fr       */
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

static int	__strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return (0);
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
		if (dot == 0 || __strncmp(tmp, "cub", 4) != 0)
			return (ret | (1<<ERR_EXTENTION));
		return (0);
	}
	return (ret | (1<<ERR_EXTENTION));
}

int	__check_file(char **av, int	*fd)
{
	int	err;

	err = __check_extention(av[0]);
	*fd = open(av[0], O_RDONLY);
	printf("in __check_file fd = %d \n", *fd);
	printf("errno %d \n", errno);
	if (*fd == -1)
	{
		if ((errno ^ EISDIR) == 0)
			err |= (1<<ERR_FOLDER);
		else if ((errno ^ EACCES) == 0)
			err |= (1<<ERR_CHMOD);
		else if ((errno ^ ENOENT) == 0)
			err |= (1<<ERR_PATH);
		else
		{
			perror("cub3d");
			exit(errno);
		}
	}
	return (err);
}

/*****************************************************************
 * Set nth bit of integer x to 1 --> x | (1<<n)
 * errno val
 * 		EACCES : cant open file du to accessibility issue
 * 		EISDIR : user is trying to open a directory
 * 		ENOENT : file does not exist and O_CREAT flag is not set
 * if open syscall fails for other reason, free all and exit;
*****************************************************************/
