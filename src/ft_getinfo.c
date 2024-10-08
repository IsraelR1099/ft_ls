/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getinfo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:38:33 by irifarac          #+#    #+#             */
/*   Updated: 2024/08/20 18:47:34 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "ft_printf.h"

static enum e_filetype	ft_get_filetype(t_fileinfo *tmp)
{
	if (S_ISREG(tmp->stat.st_mode))
	{
		ft_printf(1, "regular file\n");
		return (ft_reg);
	}
	else if (S_ISDIR(tmp->stat.st_mode))
	{
		ft_printf(1, "Direcory\n");
		return (ft_dir);
	}
	else if (S_ISCHR(tmp->stat.st_mode))
	{
		ft_printf(1, "character special file\n");
		return (ft_chr);
	}
	else if (S_ISBLK(tmp->stat.st_mode))
	{
		ft_printf(1, "block special file\n");
		return (ft_blk);
	}
	else if (S_ISFIFO(tmp->stat.st_mode))
	{
		ft_printf(1, "pipe or fifo\n");
		return (ft_fifo);
	}
	else if (S_ISLNK(tmp->stat.st_mode))
	{
		ft_printf(1, "symbolic link\n");
		return (ft_lnk);
	}
	else if (S_ISSOCK(tmp->stat.st_mode))
	{
		ft_printf(1, "socket\n");
		return (ft_sock);
	}
	return (ft_unknown);
}

void	ft_getinfo(t_fileinfo **files)
{
	t_fileinfo	*tmp;

	tmp = *files;
	while (tmp)
	{
		if (lstat(tmp->name, &tmp->stat) < 0)
		{
			ft_printf(2, "ft_ls: cannot access '%s': No such file or directory\n", tmp->name);
		}
		tmp->filetype = ft_get_filetype(tmp);
		if (tmp->filetype == ft_unknown)
			ft_printf(2, "ft_ls: unknown file type\n");
		tmp = tmp->next;
	}
}
