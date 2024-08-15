/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:33:06 by irifarac          #+#    #+#             */
/*   Updated: 2024/08/15 21:25:13 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "libft.h"

void	ft_free_fileinfo(t_fileinfo *fileinfo)
{
	t_fileinfo	*tmp;
	t_fileinfo	*cast;

	cast = fileinfo;
	while (cast != NULL)
	{
		tmp = cast;
		cast = cast->next;
		free((char *)tmp->name);
		free((char *)tmp->fullpath);
		free(tmp);
	}
}

void	ft_free_dir(t_directory *dir)
{
	t_directory	*tmp;
	t_directory	*cast;

	cast = dir;
	while (cast != NULL)
	{
		tmp = cast;
		cast = cast->next;
		free((char *)tmp->name);
		free(tmp);
	}
}

enum e_valid	ft_flags(const char *argv)
{
	char	*etmp;
	char	*tmp;

	if (!ft_strchr(argv, '-'))
		return (file);
	if (ft_strlen(argv) == 1 && *argv == '-')
		return (file);
	tmp = (char *)argv;
	etmp = (char *)argv + ft_strlen(argv);
	while (tmp < etmp)
	{
		if (*tmp == '-')
		{
			if (*argv == '-' && (tmp - argv) > 0)
				return (not_valid_flag);
			if (*argv != '-' && (tmp - argv) > 0)
				return (file);
		}
		tmp++;
	}
	return (valid_flag);
}

size_t	ft_max_len(t_fileinfo *files, t_directory *dir)
{
	size_t	max_len;
	size_t	len_file;
	size_t	len_dir;
	t_fileinfo	*tmp;
	t_directory	*tmp_dir;

	max_len = 0;
	len_file = 0;
	tmp = files;
	while (tmp != NULL)
	{
		len_file = ft_strlen(tmp->name);
		if (len_file > max_len)
			max_len = len_file;
		tmp = tmp->next;
	}
	len_dir = 0;
	tmp_dir = dir;
	while (tmp_dir != NULL)
	{
		len_dir = ft_strlen(tmp_dir->name);
		if (len_dir > max_len)
			max_len = len_dir;
		tmp_dir = tmp_dir->next;
	}
	return (max_len);
}
