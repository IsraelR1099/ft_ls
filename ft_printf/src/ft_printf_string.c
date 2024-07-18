/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 10:04:24 by irifarac          #+#    #+#             */
/*   Updated: 2024/07/17 20:43:55 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../libft/src/libft.h"

int	ft_putchar(int fd, char c)
{
	if (fd < 0)
		return (-1);
	return (write(fd, &c, 1));
}

int	ft_putstr(int fd, char *str)
{
	if (fd < 0)
		return (-1);
	if (str == NULL)
		return (write(fd, "(null)", 6));
	return (write(fd, str, ft_strlen(str)));
}
