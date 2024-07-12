/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:53:57 by irifarac          #+#    #+#             */
/*   Updated: 2024/07/12 13:04:34 by irifarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "ft_printf.h"

typedef void	t_print(const char *name, const struct stat *stat, t_flags flag);

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
		count++;
	}
	return (count);
}

/*static void	t_print_dir(t_fileinfo *tmp, t_flags flags, int entries)
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

	if (flags.long_format == true)
	{
		ft_printf(1, (S_ISDIR(stat->st_mode)) ? "d" : "-" );
		ft_printf(1, (stat->st_mode & S_IRUSR) ? "r" : "-");
		ft_printf(1, (stat->st_mode & S_IWUSR) ? "w" : "-");
		ft_printf(1, (stat->st_mode & S_IXUSR) ? "x" : "-");
		ft_printf(1, (stat->st_mode & S_IRGRP) ? "r" : "-");
		ft_printf(1, (stat->st_mode & S_IWGRP) ? "w" : "-");
		ft_printf(1, (stat->st_mode & S_IXGRP) ? "x" : "-");
		ft_printf(1, (stat->st_mode & S_IROTH) ? "r" : "-");
		ft_printf(1, (stat->st_mode & S_IWOTH) ? "w" : "-");
		ft_printf(1, (stat->st_mode & S_IXOTH) ? "x" : "-");
		ft_printf(1,"%d", stat->st_nlink);
		if (flags.print_owner == true)
		{
			pwd = getpwuid(stat->st_uid);
			ft_printf(1, "%s", pwd->pw_name);
		}
		grp = getgrgid(stat->st_gid);
		ft_printf(1 ,"%s", grp->gr_name);
	}
	ft_printf(1, " %s\n", name);
}

static void
ft_iter(t_fileinfo *tmp, t_flags flags, t_print *t_print_file)
{
	struct stat		tmpstat;
	int				n_entries;
	DIR				*dirp;
	struct dirent	*direntp;


	if (lstat(tmp->name, &tmpstat) < 0)
	{
		ft_printf(2, "lstat error\n");
		ft_panic(NULL);
	}
	if (S_ISDIR(tmpstat.st_mode) == 0)
	{
		t_print_file(tmp->name, &tmpstat, flags);
		return ;
	}
#ifdef BONUS
	if (flags.list_direc == true)
	{
		t_print_file(tmp->name, &tmpstat, flags);
		return ;
	}
#endif
	n_entries = ft_count_entries(tmp, flags);
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
		ft_printf(1, "name of entry %s\n", direntp->d_name);
	}
	ft_printf(1, "number of entries of this directory %d\n", n_entries);
	(void)flags;
}

void	ft_print_data(t_fileinfo *files, t_flags flags)
{
	t_fileinfo	*tmp;

	tmp = files;
	while (tmp)
	{
		ft_iter(tmp, flags, t_print_file);
		tmp = tmp->next;
	}
}
