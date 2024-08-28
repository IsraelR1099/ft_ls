/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:53:57 by irifarac          #+#    #+#             */
/*   Updated: 2024/08/20 21:45:53 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "ft_printf.h"
#include "libft.h"
#include "../inc/colors.h"

typedef void	t_print(const char *name, const struct stat *stat, t_flags flag);
static void	ft_iter(const char *dir_name, t_flags flags, bool print_dir, size_t count);

static void	ft_recursion(const char *dir_name, t_fileinfo *files, t_flags flags)
{
	char		*path;
	t_fileinfo	*tmp;

	tmp = files;
	while (tmp)
	{
		if (flags.recurs && S_ISDIR(tmp->stat.st_mode) &&
				ft_strcmp(tmp->name, ".") != 0 &&
				ft_strcmp(tmp->name, "..") != 0)
		{
			path = (char *)malloc(ft_strlen(dir_name) +
					ft_strlen(tmp->name) + 2);
			if (!path)
			{
				ft_printf(2, "malloc error\n");
				ft_panic(NULL);
			}
			ft_strcpy(path, dir_name);
			if (dir_name[ft_strlen(dir_name) - 1] != '/')
				ft_strcat(path, "/");
			ft_strcat(path, tmp->name);
			ft_iter(path, flags, true, 2);
			free(path);
		}
		tmp = tmp->next;
	}
}


static void	ft_print_no_sort(struct stat statbuf, char *file, const char *dir_name, t_flags flags)
{
	t_fileinfo	*files;

	files = ft_build_fileinfo(NULL, statbuf, file, dir_name);
	ft_print_file(files, &files->stat, flags);
	write(1, " ", 1);
	free((char *)files->name);
	free((char *)files->fullpath);
	free(files);
}

static void	ft_iter(const char *dir_name, t_flags flags, bool print_dir, size_t count)
{
	DIR				*dirp;
	struct dirent	*direntp;
	struct stat	statbuf;
	char		*path;
	t_fileinfo	*files;
	blkcnt_t	total_blocks;
	static int	first_call = 1;

	if (first_call && print_dir)
	{
		if (count > 1)
			ft_printf(1, "\n");
		ft_printf(1, "%s:\n", dir_name);
	}
	else if (flags.recurs)
	{
		ft_printf(1, "\n%s:\n", dir_name);
		first_call = 0;
	}
	ft_memset(&files, 0, sizeof(t_fileinfo));
	total_blocks = 0;
	dirp = opendir(dir_name);
	if (!dirp)
	{
		ft_printf(2, "ft_ls: cannot open directory '%s': %s\n", dir_name, strerror(errno));
		//ft_panic(NULL);
		return ;
	}
	while ((direntp = readdir(dirp)) != NULL)
	{
		if (flags.hidden_files == false)
			if (direntp->d_name[0] == '.')
				continue ;
		path = (char *)malloc(ft_strlen(dir_name) + ft_strlen(direntp->d_name) + 2);
		if (!path)
		{
			ft_printf(2, "malloc error\n");
			ft_panic(NULL);
		}
		ft_memset(path, 0, ft_strlen(dir_name) + ft_strlen(direntp->d_name) + 2);
		ft_strcpy(path, dir_name);
		if (dir_name[ft_strlen(dir_name) - 1] != '/')
			ft_strcat(path, "/");
		ft_strcat(path, direntp->d_name);
		if (lstat(path, &statbuf) == -1)
		{
			ft_printf(2, "ft_ls: cannot access '%s': No such file or directory\n", path);
			continue ;
		}
		if (flags.no_sort == true && flags.recurs == false)
			ft_print_no_sort(statbuf, direntp->d_name, dir_name, flags);
		else
			files = ft_build_fileinfo(files, statbuf, direntp->d_name, dir_name);
		total_blocks += statbuf.st_blocks;
		free(path);
	}
	closedir(dirp);
	ft_sort_files(&files, flags);
	if (flags.long_format)
		ft_printf(1, "total %lld\n", total_blocks / 2);
	ft_print_data(files, NULL, flags);
	if (flags.recurs)
		ft_recursion(dir_name, files, flags);
	ft_free_fileinfo(files);
}

void	ft_print_data(t_fileinfo *files, t_directory *dir, t_flags flags)
{
	t_directory	*tmp_dir;
	size_t		count;
	bool		print_dir;
	size_t		max_len;
	size_t		n_files;

	max_len = ft_max_len(files, dir);
	n_files = ft_count(files, dir);
	ft_iter_file(files, flags, max_len, n_files);
	if (flags.long_format == false && files)
		write(1, "\n", 1);
	tmp_dir = dir;
	print_dir = true;
	count = 0;
	for (t_directory *tmpd = dir; tmpd; tmpd = tmpd->next)
		count++;
	if (files)
		count++;
	if (count == 1)
	{
		if (flags.long_format == true && !files)
			print_dir = false;
		else if (flags.no_sort == true)
			print_dir = false;
		else if (flags.long_format == false)
			print_dir = false;
	}
	while (tmp_dir)
	{
		ft_iter(tmp_dir->name, flags, print_dir, count);
		tmp_dir = tmp_dir->next;
	}
}
