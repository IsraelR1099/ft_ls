/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:34:42 by israel            #+#    #+#             */
/*   Updated: 2024/07/10 13:15:45 by irifarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "ft_printf.h"

static void	ft_getopt(t_flags *flags, const char *str_flag)
{
	printf("str flag es %s\n", str_flag);
	while (*str_flag)
	{
		if (*str_flag == 'l')
			flags->long_format = true;
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
			flags->print_owner = true;
			flags->long_format = true;
		}
		else if (*str_flag == 'f')
		{
			flags->no_sort = true;
			flags->hiden_files = true;
			if (flags->sort_mtime == false)
				flags->reverse = false;
		}
		else if (*str_flag == 'd')
			flags->list_direc = true;
		else if (*str_flag == 'u')
		{
			flags->sort_atime = true;
			flags->sort_mtime = false;
			flags->time_type = time_atime;
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

t_fileinfo	*ft_parse(int argc, char **argv, t_flags *flags)
{
	int			i;
	int			value;
	t_fileinfo	*files;
	t_fileinfo	*tmp;

	i = 0;
	value = 0;
	files = NULL;
	while (i < argc)
	{
		value = ft_flags(argv[i]);
		if (value == valid_flag)
			ft_getopt(flags, argv[i]);
		else if (value == not_valid_flag)
		{
			ft_printf(1, "ft_ls: invalid option -- '%s'\n", argv[i]);
			ft_panic(files);
		}
		else if (value == file)
		{
			if (!files && i != 0)
			{
				files = ft_build_fileinfo(argv[i]);
				tmp = files;
			}
			else
			{
				tmp->next = ft_build_fileinfo(argv[i]);
				tmp = tmp->next;
			}
		}
		i++;
	}
	if (!files)
		files = ft_build_fileinfo(".");
	return (files);
}
