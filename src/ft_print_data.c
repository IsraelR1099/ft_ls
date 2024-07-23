/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:53:57 by irifarac          #+#    #+#             */
/*   Updated: 2024/07/22 18:52:35 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "ft_printf.h"
#include "libft.h"

typedef void	t_print(const char *name, const struct stat *stat, t_flags flag);

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

static void	t_print_dir(t_fileinfo *tmp, t_flags flags, int entries)
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
		t_printf(2, "opendir error\n");
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
		t_printf(1, "entries name is %s\n", array_ptr[i]->d_name);
	}
	closedir(dirp);
	(void)flags;
}

void	t_print_data(t_fileinfo *files, t_flags flags)
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
				t_print_dir(tmp, flags, entries);
			}
			else
				t_print_files(tmp, flags);
			tmp = tmp->next;
		}
	}
}*/

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
		ft_printf(1, "%s ", name);
	}
}

static void	ft_iter(const char *dir_name, t_flags flags)
{
	//int				n_entries;
	DIR				*dirp;
	struct dirent	*direntp;
	struct stat	statbuf;
	char		*path;

	//n_entries = ft_count_entries(tmp, flags);
	ft_printf(1, "directory name is |%s|\n", dir_name);
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
		ft_strcpy(path, dir_name);
		if (ft_strcmp(dir_name, "/") != 0)
			ft_strcat(path, "/");
		printf("and the path is |%s|\n", path);
		ft_strcat(path, direntp->d_name);
		ft_printf(1, "path is |%s|\n", path);
		if (lstat(path, &statbuf) == -1)
		{
			ft_printf(2, "lstat error\n");
			continue ;
		}
		t_print_file(direntp->d_name, &statbuf, flags);
		if (flags.recurs && S_ISDIR(statbuf.st_mode) &&
				ft_strcmp(direntp->d_name, ".") != 0 &&
				ft_strcmp(direntp->d_name, "..") != 0)
		{
			ft_printf(1, "\n printo %s:\n", path);
			ft_iter(path, flags);
		}
		free(path);
	}
	//ft_printf(1, "number of entries of this directory %d\n", n_entries);
	closedir(dirp);
}

void	ft_print_data(t_fileinfo *files, t_directory *dir, t_flags flags)
{
	t_fileinfo	*tmp;
	t_directory	*tmp_dir;
	//t_fileinfo	*dir_files;
	//t_directory	*dir_dir;

	tmp = files;
	while (tmp)
	{
		t_print_file(tmp->name, &tmp->stat, flags);
		tmp = tmp->next;
	}
	tmp_dir = dir;
	while (tmp_dir)
	{
		ft_printf(1, "%s:\n", tmp_dir->name);
		ft_iter(tmp_dir->name, flags);
		t_print_file(tmp_dir->name, &tmp_dir->stat, flags);
		tmp_dir = tmp_dir->next;
	}
	ft_printf(1, "\n");
}
