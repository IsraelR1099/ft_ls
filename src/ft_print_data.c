/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:53:57 by irifarac          #+#    #+#             */
/*   Updated: 2024/07/08 12:30:51 by irifarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

static void	ft_print_dir(t_fileinfo *tmp, t_flags flags)
{
	DIR				*dirp;
	struct dirent	*direntp;

	dirp = opendir(tmp->name);
	if (!dirp)
	{
		ft_printf(2, "opendir error\n");
		ft_panic(NULL);
	}
	while ((direntp = readdir(dirp)) != NULL)
	{
		printf("%s ", direntp->d_name);
	}
	closedir(dirp);
	(void)flags;
}

static void	ft_print_files(t_fileinfo *tmp, t_flags flags)
{
	(void)flags;
	(void)tmp;
}

void	ft_print_data(t_fileinfo *files, t_flags flags)
{
	t_fileinfo	*tmp;

	tmp = files;
	if (flags.long_format == false)
	{
		while (tmp)
		{
			if (tmp->filetype == ft_dir)
				ft_print_dir(tmp, flags);
			else
				ft_print_files(tmp, flags);
			tmp = tmp->next;
		}
	}
}
