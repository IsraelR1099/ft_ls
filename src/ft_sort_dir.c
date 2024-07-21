/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:59:38 by israel            #+#    #+#             */
/*   Updated: 2024/07/19 12:19:18 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "libft.h"

static void	ft_swap_entries(t_directory *tmp, t_directory *tmp2)
{
	const char	*name_temp;
	struct stat	stat_temp;
	enum e_filetype	type_temp;

	type_temp = tmp->filetype;
	name_temp = tmp->name;
	stat_temp = tmp->stat;
	tmp->filetype = tmp2->filetype;
	tmp->name = tmp2->name;
	tmp->stat = tmp2->stat;

	tmp2->filetype = type_temp;
	tmp2->name = name_temp;
	tmp2->stat = stat_temp;
}

static void	ft_sort_alpha(t_entry **dir)
{
	t_directory	*tmp;
	t_directory	*tmp2;

	tmp = (t_directory *)*dir;
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

void	ft_sort_dir(t_entry **dir, t_flags flags)
{
	for (t_directory *tmp = (t_directory *)*dir; tmp; tmp = tmp->next)
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
		ft_sort_alpha(dir);
	for (t_directory *tmp = (t_directory *)*dir; tmp; tmp = tmp->next)
		printf("name despues en sort %s\n", tmp->name);
}
