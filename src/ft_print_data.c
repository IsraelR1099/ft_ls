/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:53:57 by irifarac          #+#    #+#             */
/*   Updated: 2024/07/16 20:52:39 by israel           ###   ########.fr       */
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
	printf("file name: %s\n", files->name);
}

static struct stat
ft_iter(t_fileinfo *tmp, t_flags flags)
{
//	struct stat		tmpstat;
	int				n_entries;
	DIR				*dirp;
	struct dirent	*direntp;


/*	if (lstat(tmp->name, &tmpstat) < 0)
	{
		ft_printf(2, "lstat error\n");
		ft_panic(NULL);
	}
	if (S_ISDIR(tmpstat.st_mode) == 0)
	{
		return (tmpstat);
	}*/
	if (tmp->filetype != ft_dir)
	{
		return (tmp->stat);
	}
#ifdef BONUS
	if (flags.list_direc == true)
	{
		return (tmpstat);
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
	closedir(dirp);
	return (tmpstat);
}

//void	ft_print_data(t_fileinfo *files, t_flags flags)
void	ft_print_data(t_entry *files, t_flags flags)
{
	t_fileinfo	*tmp;

	tmp = (t_fileinfo *)files;
	printf("entro en ft_print_data name es %s\n", tmp->name);
	while (tmp)
	{
		tmp->stat = ft_iter(tmp, flags);
		ft_printf(1, "file type %d\n", tmp->filetype);
		tmp = tmp->next;
	}
	tmp = (t_fileinfo *)files;
	while (tmp)
	{
		if (tmp->filetype == ft_dir)
		{
			ft_printf(1, "directory name %s\n", tmp->name);
		}
		else
		{
			t_print_file(tmp->name, &tmp->stat, flags);
		}
		tmp = tmp->next;
	}
}
