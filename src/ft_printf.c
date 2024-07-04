/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:06:46 by israel            #+#    #+#             */
/*   Updated: 2024/07/04 13:52:24 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

static void	ft_putchar(int fd, char c)
{
	if (write(fd, &c, 1) < 0)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
}

void	ft_printf(int fd, const char *fmt, ...)
{
	char	*str;
	int	c;
	int	i;
	int	state;
	va_list	args;

	va_start(args, fmt);
	state = 0;
	for (i = 0; fmt[i]; i++)
	{
		c = fmt[i] & 0xff;
		if (state == 0)
		{
			if (c == '%')
				state = '%';
			else
				ft_putchar(fd, c);
		}
		else if (state == '%')
		{
			if (c == 's')
			{
				str = va_arg(args, char *);
				if (str == NULL)
					str = "(null)";
				while (*str)
				{
					ft_putchar(fd, *str);
					str++;
				}
			}
			else if (c == 'c')
			{
				c = va_arg(args, int);
				ft_putchar(fd, c);
			}
			state = 0;
		}
	}
	va_end(args);
}
