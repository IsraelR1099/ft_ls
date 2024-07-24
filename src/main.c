/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:29:26 by irifarac          #+#    #+#             */
/*   Updated: 2024/07/24 13:11:31 by irifarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "libft.h"

/*	printf("long format: %d\n", flags.long_format);
	printf("recursive : %d\n", flags.recurs);
	printf("hidden    : %d\n", flags.hidden_files);
	printf("reverse   : %d\n", flags.reverse);
	printf("sort time : %d\n", flags.sort_mtime);
	printf("sort atime : %d\n", flags.sort_atime);
	printf("print owner: %d\n", flags.print_owner);
	printf("no sort   : %d\n", flags.no_sort);
	printf("list directories: %d\n", flags.list_direc);*/

	//ft_free_fileinfo(files);
int	main(int argc, char **argv)
{
	t_flags		flags;
	t_fileinfo	*files;
	t_directory	*dir;
	t_entry		*entry;

	ft_memset(&files, 0, sizeof(t_fileinfo));
	ft_memset(&dir, 0, sizeof(t_directory));
	ft_memset(&flags, 0, sizeof(t_flags));
	flags.print_owner = true;
	ft_parse_flags(argc, argv, &flags);
	ft_parse(argc, argv, &files, &dir);
	ft_sort_files(&files, flags);
	entry = (t_entry *)dir;
	ft_sort_dir(&entry, flags);
	ft_print_data(files, dir, flags);
	exit (0);
}
