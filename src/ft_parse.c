/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:34:42 by israel            #+#    #+#             */
/*   Updated: 2024/08/07 20:54:19 by israel           ###   ########.fr       */
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

void	ft_parse(int argc, char **argv, t_fileinfo **files, t_directory **dir)
{
	int			i;
	struct stat	statbuf;

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
		if (S_ISDIR(statbuf.st_mode))
			*dir = ft_build_dir(*dir, statbuf, argv[i]);
		else
			*files = ft_build_fileinfo(*files, statbuf, argv[i], "./");
		i++;
	}
	if (!*dir && !*files && ft_count_files(argc, argv) == 0)
	{
		if (lstat(".", &statbuf) == -1)
			ft_printf(2, "ft_ls: cannot access '%s': %s\n", ".", strerror(errno));
		*dir = ft_build_dir(NULL, statbuf, ".");
	}
}
