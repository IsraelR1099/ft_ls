/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:53:57 by irifarac          #+#    #+#             */
/*   Updated: 2024/07/09 18:46:36 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

static int	ft_count_entries(t_fileinfo *tmp)
{
	DIR				*dirp;
	struct dirent	*direntp;
	size_t			count;

	count = 0;
	dirp = opendir(tmp->name);
	if (!dirp)
	{
		ft_printf(2, "opendir error\n");
		ft_panic(NULL);
	}
	while ((direntp = readdir(dirp)) != NULL)
	{
		count++;
	}
	return (count);
}

static void	ft_print_dir(t_fileinfo *tmp, t_flags flags, int entries)
{
	(void)flags;
	(void)tmp;
	(void)entries;
}

static void	ft_print_files(t_fileinfo *tmp, t_flags flags)
{
	(void)flags;
	(void)tmp;
}

void	ft_print_data(t_fileinfo *files, t_flags flags)
{
	t_fileinfo	*tmp;
	int		entries;

	tmp = files;
	if (flags.long_format == false)
	{
		while (tmp)
		{
			if (tmp->filetype == ft_dir)
			{
				entries = ft_count_entries(tmp);
				ft_print_dir(tmp, flags, entries);
			}
			else
				ft_print_files(tmp, flags);
			tmp = tmp->next;
		}
	}
}
