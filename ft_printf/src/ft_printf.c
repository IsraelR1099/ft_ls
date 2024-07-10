/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:31:25 by irifarac          #+#    #+#             */
/*   Updated: 2024/07/10 12:52:35 by irifarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	ft_specifier(int fd, va_list lst, int str)
{
	int		result;
	char	*ptr;

	result = 0;
	if (str == 'c')
		result = ft_putchar(fd, va_arg(lst, int));
	else if (str == 's')
		result = ft_putstr(fd, va_arg(lst, char *));
	else if (str == 'p')
		result = ft_putptr(fd, va_arg(lst, unsigned long long));
	else if (str == 'd' || str == 'i')
	{
		ptr = ft_print_itoa(va_arg(lst, int), 10);
		result = ft_putstr(fd, ptr);
		free(ptr);
	}
	else if (str == 'u')
		result = ft_putunsigned(fd, va_arg(lst, unsigned int));
	else if (str == 'x' || str == 'X')
		result = ft_puthex(fd, va_arg(lst, unsigned int), str);
	else if (str == '%')
		result = ft_putchar(fd, '%');
	else
		result = ft_putchar(fd, str);
	return (result);
}

int	ft_printf(int fd, const char *str, ...)
{
	va_list	lst;
	int		result;
	int		ret;

	va_start(lst, str);
	result = 0;
	ret = 0;
	while (*str)
	{
		if (*str == '%')
		{
			ret = ft_specifier(fd, lst, *(str + 1));
			str += 1;
		}
		else
			ret = ft_putchar(fd, *str);
		if (ret == -1)
			return (-1);
		result += ret;
		str += 1;
	}
	va_end(lst);
	return (result);
}
