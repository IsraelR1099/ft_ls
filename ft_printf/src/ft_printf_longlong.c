/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_longlong.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:13:17 by israel            #+#    #+#             */
/*   Updated: 2024/08/06 18:19:04 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../libft/src/libft.h"

int	ft_putlonglong(int fd, long long n)
{
	int		len;
	char	*ptr;

	ptr = ft_print_itoa(n, 10);
	ft_putstr(fd, ptr);
	len = ft_strlen(ptr);
	free(ptr);
	return (len);
}
