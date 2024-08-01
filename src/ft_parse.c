/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:34:42 by israel            #+#    #+#             */
/*   Updated: 2024/07/31 14:36:58 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "ft_printf.h"

void	ft_parse(int argc, char **argv, t_fileinfo **files, t_directory **dir)
{
	int			i;
	struct stat	statbuf;

	i = 1;
	printf("argc: %d\n", argc);
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
			*files = ft_build_fileinfo(*files, statbuf, argv[i]);
		i++;
	}
	printf("i es: %d\n", i);
	if (!*dir && !*files)
	{
		if (lstat(".", &statbuf) == -1)
			ft_printf(2, "ft_ls: cannot access '%s': %s\n", ".", strerror(errno));
		*dir = ft_build_dir(NULL, statbuf, ".");
	}
}
