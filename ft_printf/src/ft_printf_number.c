/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <irifarac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:10:07 by irifarac          #+#    #+#             */
/*   Updated: 2024/08/04 21:22:07 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../libft/src/libft.h"

int	ft_putint(int fd, int n)
{
	char	*ptr;
	int		len;

	ptr = ft_print_itoa(n, 10);
	ft_putstr(fd, ptr);
	len = ft_strlen(ptr);
	free(ptr);
	return (len);
}

int	ft_putunsigned(int fd, long long int n)
{
	unsigned int	number;
	char			*ptr;
	int				len;

	if (n < 0)
	{
		number = UINT_MAX - n;
		ptr = ft_print_itoa(number, 10);
		ft_putstr(fd, ptr);
		len = ft_strlen(ptr);
		free(ptr);
		return (len);
	}
	else
	{
		ptr = ft_print_itoa(n, 10);
		ft_putstr(fd, ptr);
		len = ft_strlen(ptr);
	}
	free(ptr);
	return (len);
}

long	ft_putlong(int fd, long n)
{
	char	*ptr;
	int		len;

	ptr = ft_print_itoa(n, 10);
	ft_putstr(fd, ptr);
	len = ft_strlen(ptr);
	free(ptr);
	return (len);
}

int	ft_puthex(int fd, unsigned int n, int str)
{
	char	*ptr;
	size_t	position;
	int		len;

	position = 0;
	ptr = ft_print_itoa(n, 16);
	while (ptr[position] != '\0')
	{
		if (ptr[position] > 57 && ptr[position] < 64)
		{
			ptr[position] = ptr[position] + 7;
			if (str == 'x')
				ptr[position] = ft_tolower(ptr[position]);
		}
		position++;
	}
	ft_putstr(fd, ptr);
	len = ft_strlen(ptr);
	free(ptr);
	return (len);
}

int	ft_putptr(int fd, unsigned long long ptr)
{
	char	*ptr2;
	int		position;
	int		len;

	ptr2 = ft_unsigned_itoa(ptr, 16);
	position = 0;
	while (ptr2[position] != '\0')
	{
		if (ptr2[position] > 57 && ptr2[position] < 64)
		{
			ptr2[position] = ptr2[position] + 7;
			ptr2[position] = ft_tolower(ptr2[position]);
		}
		position++;
	}
	ft_putstr(fd, "0x");
	len = ft_putstr(fd, ptr2);
	free(ptr2);
	return (len + 2);
}
