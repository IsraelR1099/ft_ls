/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:59:38 by israel            #+#    #+#             */
/*   Updated: 2024/07/29 20:39:48 by israel           ###   ########.fr       */
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

static int	ft_compare_mtime(t_directory *a, t_directory *b)
{
	if (a->stat.st_mtime > b->stat.st_mtime)
		return (-1);
	else if (a->stat.st_mtime < b->stat.st_mtime)
		return (1);
	return (0);
}

static void	ft_sort_alpha(t_directory **dir)
{
	t_directory	*tmp;
	t_directory	*tmp2;

	tmp = *dir;
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

static void	ft_sort_time(t_directory **dir)
{
	t_directory	*tmp;
	t_directory	*tmp2;

	tmp = *dir;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_compare_mtime(tmp, tmp2) > 0)
				ft_swap_entries(tmp, tmp2);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

static void	ft_reverse_dir(t_directory **dir)
{
	t_directory	*tmp;
	t_directory	*prev;
	t_directory	*next;

	tmp = *dir;
	prev = NULL;
	while (tmp)
	{
		next = tmp->next;
		tmp->next = prev;
		prev = tmp;
		tmp = next;
	}
	*dir = prev;
}

void	ft_sort_dir(t_directory **dir, t_flags flags)
{
	if (flags.no_sort)
		return ;
	if (flags.sort_mtime)
	{
		ft_sort_time(dir);
		printf("sort by time\n");
	}
	else if (flags.sort_atime)
	{
		//ft_sort_atime(files);
		printf("sort by atime\n");
	}
	else
		ft_sort_alpha(dir);
	if (flags.reverse)
		ft_reverse_dir((t_directory **)dir);
}
