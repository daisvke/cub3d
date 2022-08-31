/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 19:03:37 by lchan             #+#    #+#             */
/*   Updated: 2022/08/31 12:21:50 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	__free_parsing(t_c3d *env)
{
	char	**tmp;

	if (env->map)
	{
		tmp = env->map;
		while (*tmp)
		{
			free(*tmp);
			tmp++;
		}
		free(env->map);
		env->map = NULL;
	}
}

void	__putstr_err(const char *err_message)
{
	write (STDERR_FILENO, err_message, ft_strlen((char *)err_message));
}

void	__print_err(int	err)
{
	int			n_bit;
	const char	*err_msg[] = {
	[ERR_NO_FILE] = MESS_NO_FILE, [ERR_EXTENTION] = MESS_EXTENTION,
	[ERR_FOLDER] = MESS_FOLDER, [ERR_CHMOD] = MESS_CHMOD, [ERR_PATH] = MESS_PATH,
	};

	if (err)
	{
		n_bit = -1;
		__putstr_err(MESS_ERR_LST);
		while (++n_bit < NBR_PARSING_ERR )
			if ((err >> n_bit) & 1)
				__putstr_err(err_msg[n_bit]);
	}
}

/*****************************
 * __check_file opens the file
 * __check_map closes the file
 * ***************************/
void	__c3d_parse_map(t_c3d *env, t_player *player, char **argv)
{
	int	err;
	int	fd;
	(void) env;
	(void) player;

	err = 0;
	fd = -1;
	err += __check_file(argv + 1, &fd);
	if (! err)
		err += __check_map(env, player, fd);
	if (err)
	{
		//printf("err flag = %d\n", err);
		__print_err(err);
		exit(err);
	}
	if (err)
	{
		printf("err flag = %d\n", err);
	}
}
