/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:38:07 by israel            #+#    #+#             */
/*   Updated: 2024/08/15 21:43:10 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "ft_printf.h"
#include "libft.h"

static void	ft_print_sbl(t_fileinfo *file)
{
	char	target[1024] = {0};
	char	path[1024] = {0};
	ssize_t	len;

	len = 0;
	ft_strcpy(path, file->fullpath);
	if (ft_strcmp(path, "/") != 0)
		ft_strcat(path, "/");
	ft_strcat(path, file->name);
	ft_printf(1, "%s -> ", file->name);
	len = readlink(path, target, sizeof(target));
	if (len < 0)
	{
		ft_printf(2, "readlink error: %s\n", strerror(errno));
		return ;
	}
	target[len] = '\0';
#ifdef BONUS
	ft_print_colors(target, &file->stat);
#else
	ft_printf(1, "%s\n", target);
#endif
}

void	ft_print_file(t_fileinfo *file, struct stat *statbuf, t_flags flags)
{
	struct passwd	*pwd;
	struct group	*grp;
	char		*formatted_time;

	if (flags.long_format == true)
	{
		if (S_ISDIR(statbuf->st_mode))
			ft_printf(1, "d");
		else if (S_ISLNK(statbuf->st_mode))
			ft_printf(1, "l");
		else if (S_ISCHR(statbuf->st_mode))
			ft_printf(1, "c");
		else if (S_ISBLK(statbuf->st_mode))
			ft_printf(1, "b");
		else if (S_ISFIFO(statbuf->st_mode))
			ft_printf(1, "p");
		else if (S_ISSOCK(statbuf->st_mode))
			ft_printf(1, "s");
		else
			ft_printf(1, "-");
		ft_printf(1, (statbuf->st_mode & S_IRUSR) ? "r" : "-");
		ft_printf(1, (statbuf->st_mode & S_IWUSR) ? "w" : "-");
		ft_printf(1, (statbuf->st_mode & S_IXUSR) ? "x" : "-");
		ft_printf(1, (statbuf->st_mode & S_IRGRP) ? "r" : "-");
		ft_printf(1, (statbuf->st_mode & S_IWGRP) ? "w" : "-");
		ft_printf(1, (statbuf->st_mode & S_IXGRP) ? "x" : "-");
		ft_printf(1, (statbuf->st_mode & S_IROTH) ? "r" : "-");
		ft_printf(1, (statbuf->st_mode & S_IWOTH) ? "w" : "-");
		ft_printf(1, (statbuf->st_mode & S_IXOTH) ? "x" : "-");
		ft_printf(1," %d ", statbuf->st_nlink);
		if (flags.print_owner == true)
		{
			pwd = getpwuid(statbuf->st_uid);
			ft_printf(1, "%s ", pwd->pw_name);
		}
		grp = getgrgid(statbuf->st_gid);
		ft_printf(1 ,"%s ", grp->gr_name);
		if (S_ISCHR(statbuf->st_mode) || S_ISBLK(statbuf->st_mode))
			ft_printf(1, "%d, %d ", major(statbuf->st_rdev), minor(statbuf->st_rdev));
		else
			ft_printf(1, "%ld ", statbuf->st_size);
		formatted_time = ctime(&statbuf->st_mtime);
		formatted_time[16] = '\0';
		ft_printf(1, "%s ", formatted_time + 4);
		if (S_ISLNK(statbuf->st_mode))
			ft_print_sbl(file);
#ifdef BONUS
		else
			ft_print_colors(file->name, statbuf);
#else
		else
			ft_printf(1, "%s\n", file->name);
#endif
	}
	else
		ft_printf(1, "%s", file->name);
}

