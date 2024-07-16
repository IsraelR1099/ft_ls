/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:59:38 by israel            #+#    #+#             */
/*   Updated: 2024/07/15 20:48:38 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "libft.h"

static void	ft_swap_entries(t_fileinfo *tmp, t_fileinfo *tmp2)
{
	const char	*name_temp;
	struct stat	stat_temp;

	name_temp = tmp->name;
	stat_temp = tmp->stat;
	tmp->name = tmp2->name;
	tmp->stat = tmp2->stat;

	tmp2->name = name_temp;
	tmp2->stat = stat_temp;
}

static void	ft_sort_alpha(t_entry **files)
{
	t_fileinfo	*tmp;
	t_fileinfo	*tmp2;

	tmp = (t_fileinfo *)*files;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp->name, tmp2->name) > 0)
			{
				printf("swap\n");
				printf("tmp->name %s\n", tmp->name);
				printf("tmp2->name %s\n", tmp2->name);
				ft_swap_entries(tmp, tmp2);
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

void	ft_sort_files(t_entry **files, t_flags flags)
{
	for (t_fileinfo *tmp = (t_fileinfo *)*files; tmp; tmp = tmp->next)
		printf("name antes en sort %s\n", tmp->name);
	if (flags.no_sort)
		return ;
	if (flags.sort_mtime)
	{
		//ft_sort_time(files);
		printf("sort by time\n");
	}
	else if (flags.sort_atime)
	{
		//ft_sort_atime(files);
		printf("sort by atime\n");
	}
	else
		ft_sort_alpha(files);
	for (t_fileinfo *tmp = (t_fileinfo *)*files; tmp; tmp = tmp->next)
		printf("name despues en sort %s\n", tmp->name);
}
