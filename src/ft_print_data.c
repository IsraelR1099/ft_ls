/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:53:57 by irifarac          #+#    #+#             */
/*   Updated: 2024/07/24 13:00:58 by irifarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "ft_printf.h"
#include "libft.h"

typedef void	t_print(const char *name, const struct stat *stat, t_flags flag);
static void	ft_iter(const char *dir_name, t_flags flags);

/*static int	ft_count_entries(t_directory *tmp, t_flags flags)
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
		count++;
	}
	return (count);
}
*/

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
			ft_iter(path, flags);
			free(path);
		}
		tmp = tmp->next;
	}
}

static void
t_print_file(const char *name, const struct stat *stat, t_flags flags)
{
	struct passwd	*pwd;
	struct group	*grp;
	char		*formatted_time;

	if (flags.long_format == true)
	{
		if (S_ISDIR(stat->st_mode))
			ft_printf(1, "d");
		else if (S_ISLNK(stat->st_mode))
			ft_printf(1, "l");
		else if (S_ISCHR(stat->st_mode))
			ft_printf(1, "c");
		else if (S_ISBLK(stat->st_mode))
			ft_printf(1, "b");
		else if (S_ISFIFO(stat->st_mode))
			ft_printf(1, "p");
		else if (S_ISSOCK(stat->st_mode))
			ft_printf(1, "s");
		else
			ft_printf(1, "-");
		ft_printf(1, (stat->st_mode & S_IRUSR) ? "r" : "-");
		ft_printf(1, (stat->st_mode & S_IWUSR) ? "w" : "-");
		ft_printf(1, (stat->st_mode & S_IXUSR) ? "x" : "-");
		ft_printf(1, (stat->st_mode & S_IRGRP) ? "r" : "-");
		ft_printf(1, (stat->st_mode & S_IWGRP) ? "w" : "-");
		ft_printf(1, (stat->st_mode & S_IXGRP) ? "x" : "-");
		ft_printf(1, (stat->st_mode & S_IROTH) ? "r" : "-");
		ft_printf(1, (stat->st_mode & S_IWOTH) ? "w" : "-");
		ft_printf(1, (stat->st_mode & S_IXOTH) ? "x" : "-");
		ft_printf(1," %d ", stat->st_nlink);
		if (flags.print_owner == true)
		{
			pwd = getpwuid(stat->st_uid);
			ft_printf(1, "%s ", pwd->pw_name);
		}
		grp = getgrgid(stat->st_gid);
		ft_printf(1 ,"%s ", grp->gr_name);
		ft_printf(1, "%d ", stat->st_size);
		formatted_time = ctime(&stat->st_mtime);
		formatted_time[16] = '\0';
		ft_printf(1, "%s ", formatted_time + 4);
		ft_printf(1, "%s\n", name);
	}
	else
	{
		ft_printf(1, "%s", name);
	}
}

static void	ft_iter(const char *dir_name, t_flags flags)
{
	DIR				*dirp;
	struct dirent	*direntp;
	struct stat	statbuf;
	char		*path;
	t_fileinfo	*files;

	ft_memset(&files, 0, sizeof(t_fileinfo));
	if (flags.recurs)
		ft_printf(1,"%s:\n", dir_name);
	dirp = opendir(dir_name);
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
		path = (char *)malloc(ft_strlen(dir_name) + ft_strlen(direntp->d_name) + 2);
		if (!path)
		{
			ft_printf(2, "malloc error\n");
			ft_panic(NULL);
		}
		ft_memset(path, 0, sizeof(path));
		ft_strcpy(path, dir_name);
		if (dir_name[ft_strlen(dir_name) - 1] != '/')
			ft_strcat(path, "/");
		ft_strcat(path, direntp->d_name);
		if (lstat(path, &statbuf) == -1)
		{
			ft_printf(2, "ft_ls: cannot access '%s': No such file or directory\n", path);
			continue ;
		}
			files = ft_build_fileinfo(files, statbuf, direntp->d_name);
		free(path);
	}
	closedir(dirp);
	ft_sort_files(&files, flags);
	ft_print_data(files, NULL, flags);
	if (flags.recurs)
		ft_recursion(dir_name, files, flags);
	write(1, "\n", 1);
}

void	ft_print_data(t_fileinfo *files, t_directory *dir, t_flags flags)
{
	t_fileinfo	*tmp;
	t_directory	*tmp_dir;

	tmp = files;
	while (tmp)
	{
		t_print_file(tmp->name, &tmp->stat, flags);
		if (flags.recurs == false)
			write(1, " ", 1);
		tmp = tmp->next;
	}
	tmp_dir = dir;
	while (tmp_dir)
	{
		ft_iter(tmp_dir->name, flags);
		tmp_dir = tmp_dir->next;
	}
}
