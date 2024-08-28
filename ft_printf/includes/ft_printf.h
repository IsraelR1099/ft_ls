/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:30:47 by irifarac          #+#    #+#             */
/*   Updated: 2024/08/06 18:25:35 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

int		ft_printf(int fd, const char *str, ...);
int		ft_putchar(int fd, char c);
int		ft_putstr(int fd, char *str);
int		ft_putunsigned(int fd, long long int n);
int		ft_puthex(int fd, unsigned int n, int str);
int		ft_putptr(int fd, unsigned long long ptr);
//Funciones de la libreria libft
char	*ft_print_itoa(long long n, int base);
int		ft_len(long long n, int base);
int		ft_tolower(int c);
char	*ft_unsigned_itoa(unsigned long long n, int base);
int		ft_unsigned_len(unsigned long long n, int base);
long	ft_putlong(int fd, long n);
int		ft_putlonglong(int fd, long long n);
int		ft_putint(int fd, int n);

#endif
