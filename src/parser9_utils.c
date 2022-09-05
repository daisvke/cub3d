/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser8_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:07:07 by lchan             #+#    #+#             */
/*   Updated: 2022/09/04 18:22:54 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	c3d_strlen(char *str)
{
	char	*tmp;

	tmp = str;
	while (*tmp)
		tmp++;
	return (tmp - str);
}

int	c3d_strncmp(const char *s1, const char *s2, size_t n)
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

int	c3d_strchr_b(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char) c)
			return (0);
		i++;
	}
	return (-1);
}

int	c3d_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long int	c3d_atol(const char *str)
{
	int			sign;
	long int	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if ((*str == '+' || *str == '-') && str++)
		if (*(str - 1) == '-')
			sign = -sign;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * (long int)sign);
}
