/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:29:26 by irifarac          #+#    #+#             */
/*   Updated: 2024/07/17 09:45:40 by irifarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "libft.h"

int	main(int argc, char **argv)
{
	t_flags		flags;
	t_entry		*files;
//	t_fileinfo	*files;
//	t_fileinfo	*tmp;

	ft_memset(&flags, 0, sizeof(t_flags));
	flags.print_owner = true;
	files = ft_parse(argc, argv, &flags);
	ft_sort_files(&files, flags);
	ft_print_data(files, flags);
	ft_free_fileinfo(files);
	exit (0);
}
