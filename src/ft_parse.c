/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:34:42 by israel            #+#    #+#             */
/*   Updated: 2024/07/24 11:16:40 by irifarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "ft_printf.h"

void	ft_parse(int argc, char **argv, t_fileinfo **files, t_directory **dir)
{
	int			i;
	struct stat	statbuf;
	//t_fileinfo	*tmp;

	i = 1;
	while (i < argc)
	{
		if (argv[i] == NULL)
		{
			i++;
			continue ;
		}
		if (lstat(argv[i], &statbuf) == -1)
		{
			ft_printf(2, "ft_ls: %s: %s\n", argv[i], strerror(errno));
			i++;
			continue ;
		}
		if (S_ISDIR(statbuf.st_mode))
			*dir = ft_build_dir(*dir, statbuf, argv[i]);
		else
			*files = ft_build_fileinfo(*files, statbuf, argv[i]);
		i++;
	}
	if (!*dir && !*files)
	{
		if (lstat(".", &statbuf) == -1)
			ft_printf(2, "ft_ls: %s\n", strerror(errno));
		*dir = ft_build_dir(NULL, statbuf, ".");
	}
}
