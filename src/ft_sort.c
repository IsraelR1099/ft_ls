/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:59:38 by israel            #+#    #+#             */
/*   Updated: 2024/08/13 14:05:52 by israel           ###   ########.fr       */
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

static int	ft_compare_mtime(t_fileinfo *a, t_fileinfo *b)
{
#ifdef __linux__
	if (a->stat.st_mtim.tv_sec > b->stat.st_mtim.tv_sec)
		return (-1);
	else if (a->stat.st_mtim.tv_sec < b->stat.st_mtim.tv_sec)
		return (1);
	else
	{
		if (a->stat.st_mtim.tv_nsec > b->stat.st_mtim.tv_nsec)
			return (-1);
		else if (a->stat.st_mtim.tv_nsec < b->stat.st_mtim.tv_nsec)
			return (1);
		else
			return (ft_strcmp(a->name, b->name));
	}
#else
	if (a->stat.st_mtime > b->stat.st_mtime)
		return (-1);
	else if (a->stat.st_mtime < b->stat.st_mtime)
		return (1);
	else
		return (ft_strcmp(a->name, b->name));
#endif
}

static int	ft_compare_atime(t_fileinfo *a, t_fileinfo *b)
{
#ifdef __linux__
	if (a->stat.st_atim.tv_sec > b->stat.st_atim.tv_sec)
		return (-1);
	else if (a->stat.st_atim.tv_sec < b->stat.st_atim.tv_sec)
		return (1);
	else
	{
		if (a->stat.st_atim.tv_nsec > b->stat.st_atim.tv_nsec)
			return (-1);
		else if (a->stat.st_atim.tv_nsec < b->stat.st_atim.tv_nsec)
			return (1);
		else
			return (ft_strcmp(a->name, b->name));
	}
#else
	if (a->stat.st_atime > b->stat.st_atime)
		return (-1);
	else if (a->stat.st_atime < b->stat.st_atime)
		return (1);
	else
		return (ft_strcmp(a->name, b->name));
#endif
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

static void	ft_sort_time(t_fileinfo **files)
{
	t_fileinfo	*tmp;
	t_fileinfo	*tmp2;

	tmp = *files;
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

static void	ft_sort_atime(t_fileinfo **files)
{
	t_fileinfo	*tmp;
	t_fileinfo	*tmp2;

	tmp = *files;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_compare_atime(tmp, tmp2) > 0)
				ft_swap_entries(tmp, tmp2);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

static void	ft_reverse_files(t_fileinfo **files)
{
	t_fileinfo *prev;
	t_fileinfo *current;
	t_fileinfo *next;

	prev = NULL;
	current = *files;
	next = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*files = prev;
}

void	ft_sort_files(t_fileinfo **files, t_flags flags)
{
	if (flags.no_sort)
		return ;
	if (flags.sort_mtime)
	{
		ft_sort_time(files);
	}
	else if (flags.sort_atime)
	{
		ft_sort_atime(files);
		printf("sort by atime\n");
	}
	else
		ft_sort_alpha(files);
	if (flags.reverse)
		ft_reverse_files(files);
}
