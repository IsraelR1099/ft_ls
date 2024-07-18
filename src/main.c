/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:29:26 by irifarac          #+#    #+#             */
/*   Updated: 2024/07/18 21:25:43 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "libft.h"

int	main(int argc, char **argv)
{
	t_flags		flags;
	t_fileinfo	*files;
	t_directory	*dir;
	t_entry		*entry;
//	t_fileinfo	*tmp;

	ft_memset(&flags, 0, sizeof(t_flags));
	flags.print_owner = true;
	ft_parse_flags(argc, argv, &flags);
	ft_memset(&files, 0, sizeof(t_fileinfo));
	ft_memset(&dir, 0, sizeof(t_directory));
	printf("long format: %d\n", flags.long_format);
	printf("recursive : %d\n", flags.recurs);
	printf("hidden    : %d\n", flags.hidden_files);
	printf("reverse   : %d\n", flags.reverse);
	printf("sort time : %d\n", flags.sort_mtime);
	printf("sort atime : %d\n", flags.sort_atime);
	printf("print owner: %d\n", flags.print_owner);
	printf("no sort   : %d\n", flags.no_sort);
	printf("list directories: %d\n", flags.list_direc);
	ft_parse(argc, argv, &files, &dir);
	for (t_fileinfo *tmp = files; tmp; tmp = tmp->next)
	{
		printf("name: %s\n", tmp->name);
	}
	for (t_directory *tmp = dir; tmp; tmp = tmp->next)
	{
		printf("name dir: %s\n", tmp->name);
	}
	entry = (t_entry *)files;
	ft_sort_files(&entry, flags);
	for (t_fileinfo *tmp = files; tmp; tmp = tmp->next)
	{
		printf("name: %s\n", tmp->name);
	}
	/*ft_print_data(files, flags);*/
	//ft_free_fileinfo(files);
	exit (0);
}
