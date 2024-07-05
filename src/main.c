/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:29:26 by irifarac          #+#    #+#             */
/*   Updated: 2024/07/05 11:28:34 by irifarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

int	main(int argc, char **argv)
{
	t_flags		flags;
	t_fileinfo	*files;
	t_fileinfo	*tmp;

	for (int i = 0; i < argc; i++)
		printf("argv es: %s\n", argv[i]);
	ft_memset(&flags, 0, sizeof(t_flags));
	files = ft_parse(argc, argv, &flags);
	tmp = files;
	while (tmp)
	{
		printf("file name: %s\n", files->name);
		tmp = tmp->next;
	}
	printf("long_format es %d\n", flags.long_format);
	printf("recurs es %d\n", flags.recurs);
	printf("hiden_files es %d\n", flags.hiden_files);
	printf("reverse es %d\n", flags.reverse);
	printf("sort_time es %d\n", flags.sort_time);
	printf("print_owner es %d\n", flags.print_owner);
	printf("no_sort es %d\n", flags.no_sort);
	ft_free_fileinfo(files);
	exit (0);
}
