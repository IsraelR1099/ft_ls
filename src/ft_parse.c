/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:34:42 by israel            #+#    #+#             */
/*   Updated: 2024/08/19 12:17:54 by irifarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "ft_printf.h"

static int	ft_count_files(int argc, char **argv)
{
	int	count;

	count = 0;
	for (int i = 1; i < argc; i++)
	{
		if (argv[i] == NULL)
			continue ;
		if (ft_flags(argv[i]) == file)
			count++;
	}
	return (count);
}

void	ft_parse(int argc, char **argv, t_fileinfo **files, t_directory **dir, t_flags flags)
{
	int			i;
	struct stat	statbuf;
	char		*fullpath;

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
			ft_printf(2, "ft_ls: cannot access '%s': %s\n", argv[i], strerror(errno));
			i++;
			continue ;
		}
		if (argv[i][0] == '/')
			fullpath = NULL;
		else
			fullpath = "./";
		if (S_ISDIR(statbuf.st_mode)
				&& flags.list_direc == false)
			*dir = ft_build_dir(*dir, statbuf, argv[i]);
		else
			*files = ft_build_fileinfo(*files, statbuf, argv[i], fullpath);
		i++;
	}
	if (!*dir && !*files && ft_count_files(argc, argv) == 0)
	{
		if (lstat(".", &statbuf) == -1)
			ft_printf(2, "ft_ls: cannot access '%s': %s\n", ".", strerror(errno));
		if (flags.list_direc == false)
			*dir = ft_build_dir(NULL, statbuf, ".");
		else
			*files = ft_build_fileinfo(NULL, statbuf, ".", NULL);
	}
}
