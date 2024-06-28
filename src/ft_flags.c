/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:34:42 by israel            #+#    #+#             */
/*   Updated: 2024/06/28 09:47:26 by irifarac         ###   ########.fr       */
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
		str_flag++;
	}
}

void	ft_parse_flags(int argc, char **argv, t_flags *flags)
{
	int	i;
	int	j;

	if (argc == 1)
		return ;
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (*argv && argv[i][j])
		{
			if (j == 0 && argv[i][j] == '-')
				ft_getopt(flags, argv[i]);
			else if (j != 0 && argv[i][j] == '-')
			{
				printf("ls: invalid option");
				exit (2);
			}
			j++;
		}
		i++;
	}
}
