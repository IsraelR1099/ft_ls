/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:53:57 by irifarac          #+#    #+#             */
/*   Updated: 2024/07/11 18:50:46 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "ft_printf.h"

static int	ft_count_entries(t_fileinfo *tmp, t_flags flags)
{
	DIR				*dirp;
	struct dirent	*direntp;
	size_t			count;

	count = 0x0;
	dirp = opendir(tmp->name);
	if (!dirp)
	{
		ft_printf(2, "opendir error\n");
		ft_panic(NULL);
	}
	while ((direntp = readdir(dirp)) != NULL)
	{
		if (flags.hidden_files == false)
			if (direntp->d_name[0] == '.')
				continue ;
		if (flags.recurs == true)
		{
			if (tmp->filetype == ft_dir)
				count++;
		}
		count++;
	}
	return (count);
}

static void	ft_print_dir(t_fileinfo *tmp, t_flags flags, int entries)
{
	DIR				*dirp;
	struct dirent	*direntp;
	struct dirent	array[entries];
	struct dirent	*array_ptr[entries];
	int				i;

	i = 0x0;
	dirp = opendir(tmp->name);
	if (!dirp)
	{
		ft_printf(2, "opendir error\n");
		ft_panic(NULL);
	}
	while ((direntp = readdir(dirp)) != NULL)
	{
		if (flags.hidden_files == false)
			if (direntp->d_name[0] == '.')
				continue ;
		array[i] = *direntp;
		array_ptr[i] = &array[i];
		i++;
	}
	for (int i = 0; i < entries; i++)
	{
		if (S_ISDIR(array_ptr[i]->d_type))
			printf("it's not a directory\n");
		ft_printf(1, "entries name is %s\n", array_ptr[i]->d_name);
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
	int			entries;

	tmp = files;
	if (flags.long_format == false)
	{
		while (tmp)
		{
			if (tmp->filetype == ft_dir)
			{
				entries = ft_count_entries(tmp, flags);
				printf("total of entries %d\n", entries);
				ft_print_dir(tmp, flags, entries);
			}
			else
				ft_print_files(tmp, flags);
			tmp = tmp->next;
		}
	}
}
