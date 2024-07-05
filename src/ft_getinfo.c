/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getinfo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:38:33 by irifarac          #+#    #+#             */
/*   Updated: 2024/07/05 13:00:30 by irifarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

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
		printf("name es: %s\n", tmp->name);
		if (lstat(tmp->name, &tmp->stat) < 0)
		{
			ft_printf(2, "ft_ls: cannot access '%s': No such file or directory\n", tmp->name);
		}
		tmp->filetype = ft_get_filetype(tmp);
		printf("filetype es %d\n", tmp->filetype);
		printf("num of links %ld\n", tmp->stat.st_nlink);
		tmp = tmp->next;
	}
}
