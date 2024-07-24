/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:04:58 by israel            #+#    #+#             */
/*   Updated: 2024/07/24 11:33:39 by irifarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "libft.h"
#include "ft_printf.h"

t_fileinfo
*ft_build_fileinfo(t_fileinfo *file, struct stat statbuf, const char *name)
{
	t_fileinfo	*fileinfo;

	fileinfo = (t_fileinfo *)malloc(sizeof(t_fileinfo));
	if (fileinfo == NULL)
		exit (1);
	ft_memset(fileinfo, 0, sizeof(t_fileinfo));
	fileinfo->name = ft_strdup(name);
	if (fileinfo->name == NULL)
		exit (1);
	fileinfo->stat = statbuf;
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
	fileinfo->next = file;
	return (fileinfo);
}

t_directory
*ft_build_dir(t_directory *dir, struct stat statbuf, const char *name)
{
	t_directory	*directory;

	directory = (t_directory *)malloc(sizeof(t_directory));
	if (directory == NULL)
		exit (1);
	ft_memset(directory, 0, sizeof(t_directory));
	directory->name = ft_strdup(name);
	if (directory->name == NULL)
		exit (1);
	directory->stat = statbuf;
	if (S_ISDIR(statbuf.st_mode))
		directory->filetype = ft_dir;
	else if (S_ISLNK(statbuf.st_mode))
		directory->filetype = ft_lnk;
	else if (S_ISCHR(statbuf.st_mode))
		directory->filetype = ft_chr;
	else if (S_ISBLK(statbuf.st_mode))
		directory->filetype = ft_blk;
	else if (S_ISFIFO(statbuf.st_mode))
		directory->filetype = ft_fifo;
	else if (S_ISSOCK(statbuf.st_mode))
		directory->filetype = ft_sock;
	else if (S_ISREG(statbuf.st_mode))
		directory->filetype = ft_reg;
	else
		directory->filetype = ft_unknown;
	directory->next = dir;
	return (directory);
}
