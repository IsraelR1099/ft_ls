/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:31:25 by irifarac          #+#    #+#             */
/*   Updated: 2024/08/06 17:57:01 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../libft/src/libft.h"

static int	ft_specifier(int fd, va_list lst, const char *str)
{
	int		result;

	result = 0;
	if (ft_strncmp("c", str, 1) == 0)
		result = ft_putchar(fd, va_arg(lst, int));
	else if (ft_strncmp("s", str, 1) == 0)
		result = ft_putstr(fd, va_arg(lst, char *));
	else if (ft_strncmp("p", str, 1) == 0)
		result = ft_putptr(fd, va_arg(lst, unsigned long long));
	else if (ft_strncmp("d", str, 1) == 0 || ft_strncmp("i", str, 1) == 0)
		result = ft_putint(fd, va_arg(lst, int));
	else if (ft_strncmp("ld", str, 2) == 0)
		result = ft_putlong(fd, va_arg(lst, long));
	else if (ft_strncmp("lld", str, 3) == 0)
		result = ft_putlonglong(fd, va_arg(lst, long long));
	else if (ft_strncmp("u", str, 1) == 0)
		result = ft_putunsigned(fd, va_arg(lst, unsigned int));
	else if (ft_strncmp("x", str, 1) == 0 || ft_strncmp("X", str, 1) == 0)
		result = ft_puthex(fd, va_arg(lst, unsigned int), *str);
	else if (ft_strncmp("%", str, 1) == 0)
		result = ft_putchar(fd, '%');
	else
		result = ft_putchar(fd, *str);
	return (result);
}

int	ft_printf(int fd, const char *str, ...)
{
	va_list	lst;
	int		ret;

	va_start(lst, str);
	ret = 0;
	while (*str)
	{
		if (*str == '%')
		{
			ret += ft_specifier(fd, lst, str + 1);
			if (ft_strncmp("ll", str + 1, 2) == 0)
				str = str + 3;
			else if (*(str + 1) == 'l')
				str = str + 2;
			else
				str += 1;
		}
		else
			ret += ft_putchar(fd, *str);
		if (ret == -1)
			return (-1);
		str += 1;
	}
	va_end(lst);
	return (ret);
}
