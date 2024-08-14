/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:29:26 by irifarac          #+#    #+#             */
/*   Updated: 2024/08/14 11:10:04 by irifarac         ###   ########.fr       */
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

	ft_memset(&files, 0, sizeof(t_fileinfo));
	ft_memset(&dir, 0, sizeof(t_directory));
	ft_memset(&flags, 0, sizeof(t_flags));
	flags.print_owner = true;
	ft_parse_flags(argc, argv, &flags);
	ft_parse(argc, argv, &files, &dir, flags);
	if (files)
		ft_sort_files(&files, flags);
	ft_sort_dir(&dir, flags);
	ft_print_data(files, dir, flags);
	ft_free_fileinfo(files);
	ft_free_dir(dir);
	exit (0);
}
