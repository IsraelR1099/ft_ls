/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:29:26 by irifarac          #+#    #+#             */
/*   Updated: 2024/07/10 13:15:24 by irifarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "libft.h"

int	main(int argc, char **argv)
{
	t_flags		flags;
	t_fileinfo	*files;
	t_fileinfo	*tmp;

	ft_memset(&flags, 0, sizeof(t_flags));
	files = ft_parse(argc, argv, &flags);
	ft_getinfo(&files);
	ft_print_data(files, flags);
	tmp = files;
	while (tmp)
	{
		printf("file name: %s\n", tmp->name);
		tmp = tmp->next;
	}
	printf("long_format es %d\n", flags.long_format);
	printf("recurs es %d\n", flags.recurs);
	printf("hiden_files es %d\n", flags.hidden_files);
	printf("reverse es %d\n", flags.reverse);
	printf("sort_time es %d\n", flags.time_type);
	printf("print_owner es %d\n", flags.print_owner);
	printf("no_sort es %d\n", flags.no_sort);
	ft_free_fileinfo(files);
	exit (0);
}
