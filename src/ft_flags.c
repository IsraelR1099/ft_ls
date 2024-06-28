/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:34:42 by israel            #+#    #+#             */
/*   Updated: 2024/06/28 13:16:27 by irifarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

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
			flags->hiden_files = true;
		else if (*str_flag == 'r')
			flags->reverse = true;
		else if (*str_flag == 't')
			flags->sort_time = true;
		else if (*str_flag == 'g')
			flags->print_owner = true;
		else if (*str_flag == 'f')
			flags->no_sort = true;
		else if (*str_flag == 'd')
			flags->list_direc = true;
		else if (*str_flag != '-')
			printf("invalid flag: %c\n", *str_flag);
		str_flag++;
	}
}

t_fileinfo	*ft_parse(int argc, char **argv, t_flags *flags)
{
	int			i;
	int			value;
	t_fileinfo	*files;
	t_fileinfo	*tmp;

	files = ft_build_fileinfo(".");
	tmp = files;
	if (argc == 1)
		return (NULL);
	i = 1;
	value = 0;
	while (i < argc)
	{
		value = ft_flags(argv[i]);
		if (value == valid_flag)
			ft_getopt(flags, argv[i]);
		else if (value == not_valid_flag)
			printf("not valid flag\n");
		else if (value == file)
		{
			tmp->next = ft_build_fileinfo(argv[i]);
			tmp = tmp->next;
		}
		i++;
	}
	return (files);
}
