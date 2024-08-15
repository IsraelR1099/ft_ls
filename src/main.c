/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:29:26 by irifarac          #+#    #+#             */
/*   Updated: 2024/08/15 20:13:10 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "libft.h"
#include "ft_printf.h"

int	main(int argc, char **argv)
{
	t_flags		flags;
	t_fileinfo	*files;
	t_directory	*dir;
	struct winsize	size;

	ft_memset(&files, 0, sizeof(t_fileinfo));
	ft_memset(&dir, 0, sizeof(t_directory));
	ft_memset(&flags, 0, sizeof(t_flags));
	flags.print_owner = true;
	ft_parse_flags(argc, argv, &flags);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	ft_parse(argc, argv, &files, &dir, flags);
	if (files)
		ft_sort_files(&files, flags);
	ft_sort_dir(&dir, flags);
	ft_print_data(files, dir, flags);
	ft_free_fileinfo(files);
	ft_free_dir(dir);
	exit (0);
}
