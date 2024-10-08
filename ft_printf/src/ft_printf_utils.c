/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 10:07:43 by irifarac          #+#    #+#             */
/*   Updated: 2024/08/04 21:21:25 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_len(long long n, int base)
{
	long long	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= base;
		len++;
	}
	return (len);
}

char	*ft_print_itoa(long long n, int base)
{
	char		*ptr;
	size_t		len;
	long long	nbr;

	len = ft_len(n, base);
	nbr = n;
	if (n < 0)
	{
		nbr = n * (-1);
		len = len + 1;
	}
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	if (n == 0)
		*ptr = 0 + 48;
	ptr[len] = '\0';
	while (len--)
	{
		ptr[len] = (nbr % base) + 48;
		nbr /= base;
	}
	if (n < 0)
		*ptr = '-';
	return (ptr);
}
