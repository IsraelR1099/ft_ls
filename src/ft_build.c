/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:04:58 by israel            #+#    #+#             */
/*   Updated: 2024/07/16 20:28:56 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "libft.h"
#include "ft_printf.h"

t_fileinfo	*ft_build_fileinfo(const char *name)
{
	t_fileinfo	*fileinfo;
	struct stat	statbuf;

	fileinfo = (t_fileinfo *)malloc(sizeof(t_fileinfo));
	if (fileinfo == NULL)
		exit (1);
	ft_memset(fileinfo, 0, sizeof(t_fileinfo));
	fileinfo->name = ft_strdup(name);
	if (fileinfo->name == NULL)
		exit (1);
	if (lstat(name, &statbuf) == -1)
	{
		ft_printf(2, "ft_ls: %s: %s\n", name, strerror(errno));
		ft_panic(NULL);
	}
	fileinfo->linkmode = statbuf.st_mode;
	if (S_ISDIR(statbuf.st_mode))
		fileinfo->filetype = ft_dir;
	else if (S_ISLNK(statbuf.st_mode))
		fileinfo->filetype = ft_lnk;
	else if (S_ISCHR(statbuf.st_mode))
		fileinfo->filetype = ft_chr;
	else if (S_ISBLK(statbuf.st_mode))
		fileinfo->filetype = ft_blk;
	else if (S_ISFIFO(statbuf.st_mode))
		fileinfo->filetype = ft_fifo;
	else if (S_ISSOCK(statbuf.st_mode))
		fileinfo->filetype = ft_sock;
	else if (S_ISREG(statbuf.st_mode))
		fileinfo->filetype = ft_reg;
	else
		fileinfo->filetype = ft_unknown;
	return (fileinfo);
}
