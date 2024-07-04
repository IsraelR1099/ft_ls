/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:29:26 by irifarac          #+#    #+#             */
/*   Updated: 2024/07/03 21:40:41 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

int	main(int argc, char **argv)
{
	t_flags		flags;
	t_fileinfo	*files;

	ft_memset(&flags, 0, sizeof(t_flags));
	files = ft_parse(argc, argv, &flags);
	while (files)
	{
		printf("file name: %s\n", files->name);
		files = files->next;
	}
	printf("long_format es %d\n", flags.long_format);
	printf("recurs es %d\n", flags.recurs);
	printf("hiden_files es %d\n", flags.hiden_files);
	printf("reverse es %d\n", flags.reverse);
	printf("sort_time es %d\n", flags.sort_time);
	printf("print_owner es %d\n", flags.print_owner);
	printf("no_sort es %d\n", flags.no_sort);
	exit (0);
}
