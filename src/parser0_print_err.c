/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser0_print_err.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:11:18 by lchan             #+#    #+#             */
/*   Updated: 2022/09/05 23:13:48 by mint             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	nb;

	nb = n;
	if (nb < 0)
	{
		write (fd, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
		ft_putnbr_fd(nb / 10, fd);
	nb = nb % 10 + '0';
	write (fd, &nb, 1);
}

void	c3d_putstr_err(const char *err_type, const char *err_message)
{
	if (err_type)
		write (STDERR_FILENO, err_type, ft_strlen((char *) err_type));
	write (STDERR_FILENO, err_message, ft_strlen((char *)err_message));
}

void	c3d_putstr_err_line(int line, const char *err_message)
{
	c3d_putstr_err (NULL, "Line ");
	ft_putnbr_fd(line, STDERR_FILENO);
	c3d_putstr_err (NULL, err_message);
}

void	c3d_print_file_err_exit(int err)
{
	int			n_bit;
	const char	*err_msg[] = {
	[ERR_NO_FILE] = MS_NO_FILE, [ERR_EXTENTION] = MS_EXTENTION,
	[ERR_FOLDER] = MS_FOLDER, [ERR_CHMOD] = MS_CHMOD, [ERR_PATH] = MS_PATH,
	};

	n_bit = -1;
	while (++n_bit < NBR_PARSING_ERR)
		if ((err >> n_bit) & 1)
			c3d_putstr_err(NULL, err_msg[n_bit]);
	exit(err);
}

void	c3d_print_parse_err_exit(t_parser *parse, t_c3d *env)
{
	int			i;
	const char	*tab[] = {
	[ERR_EMPTY_FILE] = MS_EMPTY_FILE, [ERR_TX_KEY_MISS] = MS_TX_KEY_MISS,
	[ERR_TX_PATH] = MS_TX_PATH, [ERR_TX_PATH_LENGH] = MS_TX_PATH_LENGH,
	[ERR_FC_OVERFLOW] = MS_FC_OVERFLOW, [ERR_FC_KEY_MISS] = MS_FC_KEY_MISS,
	[ERR_FC_FORM] = MS_FC_FORM, [ERR_MP_MISPLACED] = MS_MP_MISPLACED,
	[ERR_MP_TOO_SMALL] = MS_MP_TOO_SMALL, [ERR_MP_NO_PLAYER] = MS_MP_NO_PLAYER,
	[ERR_MP_MULTI_PLAYER] = MS_MP_MULTI_PLAYER, [ERR_MP_CUTTED] = MS_MP_CUTTED,
	[ERR_MP_BORDERS] = MS_MP_BORDERS, [ERR_MP_TOO_BIG] = MS_MP_TOO_BIG,
	[ERR_MP_UNABLE_TO_CPY] = MS_MP_UNABLE_TO_CPY, [ERR_GIBBER] = MS_GIBBER,
	[ERR_FC_MULTIDEF] = MS_FC_MULTIDEF, [ERR_TX_MULTIDEF] = MS_TX_MULTIDEF,
	};

	i = -1;
	if (parse->err_buf[0][0])
		while (++i < parse->err_buf_index)
			c3d_putstr_err_line(parse->err_buf[i][0], \
				tab[parse->err_buf[i][1]]);
	i = -1;
	while (++i < ERR_GIBBER)
		if ((parse->blocking_err_flag >> i) & 1)
			c3d_putstr_err(MS_BLK_ERR, tab[i]);
	i = -1;
	while (++i <= ERR_GIBBER)
		if ((parse->blocking_err_flag >> i) & 1)
			c3d_add_to_env_exit(parse, env);
}
