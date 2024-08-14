/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 20:23:27 by israel            #+#    #+#             */
/*   Updated: 2024/08/14 09:57:04 by irifarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "ft_printf.h"

static void	ft_getopt(t_flags *flags, const char *str_flag)
{
	while (*str_flag)
	{
		if (*str_flag == 'l')
		{
			if (flags->no_sort == true)
				return ;
			flags->long_format = true;
		}
		else if (*str_flag == 'R')
			flags->recurs = true;
		else if (*str_flag == 'a')
			flags->hidden_files = true;
		else if (*str_flag == 'r')
			flags->reverse = true;
		else if (*str_flag == 't')
		{
			flags->sort_mtime = true;
			flags->sort_atime = false;
			flags->time_type = time_mtime;
		}
#ifdef BONUS
		else if (*str_flag == 'g')
		{
			flags->print_owner = false;
			flags->long_format = true;
		}
		else if (*str_flag == 'f')
		{
			flags->no_sort = true;
			flags->hidden_files = true;
			if (flags->sort_mtime == false)
				flags->reverse = false;
			if (flags->long_format == true)
				flags->long_format = false;
		}
		else if (*str_flag == 'd')
		{
			flags->list_direc = true;
			flags->recurs = false;
		}
		else if (*str_flag == 'u')
		{
			if (flags->long_format == true)
			{
				flags->sort_atime = true;
				flags->sort_mtime = false;
				flags->time_type = time_atime;
			}
		}
#endif
		else if (*str_flag != '-')
		{
			ft_printf(2, "ft_ls: invalid option -- '%c'\n", *str_flag);
			ft_panic(NULL);
		}
		str_flag++;
	}
}

void	ft_parse_flags(int argc, char **argv, t_flags *flags)
{
	int	i;
	int	value;

	i = 1;
	value = 0;
	while (i < argc)
	{
		value = ft_flags(argv[i]);
		if (value == valid_flag)
		{
			ft_getopt(flags, argv[i]);
			argv[i] = NULL;
		}
		else if (value == not_valid_flag)
		{
			ft_printf(2, "ft_ls: invalid option -- %c\n", argv[i][1]);
			ft_panic(NULL);
		}
		i++;
	}
}
