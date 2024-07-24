/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:59:38 by israel            #+#    #+#             */
/*   Updated: 2024/07/24 11:27:38 by irifarac         ###   ########.fr       */
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

static void	ft_sort_alpha(t_fileinfo **files)
{
	t_fileinfo	*tmp;
	t_fileinfo	*tmp2;

	tmp = *files;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp->name, tmp2->name) > 0)
				ft_swap_entries(tmp, tmp2);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

void	ft_sort_files(t_fileinfo **files, t_flags flags)
{
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
}
