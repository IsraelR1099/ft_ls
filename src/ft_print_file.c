/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:38:07 by israel            #+#    #+#             */
/*   Updated: 2024/08/19 12:27:35 by irifarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "ft_printf.h"
#include "libft.h"
#include "../inc/colors.h"

static void	ft_print_sbl(t_fileinfo *file, t_flags flags)
{
	char	target[1024] = {0};
	char	path[1024] = {0};
	ssize_t	len;

	len = 0;
	if (file->fullpath)
	{
		ft_strcpy(path, file->fullpath);
		if (path[ft_strlen(path) - 1] != '/')
			ft_strcat(path, "/");
	}
	ft_strcat(path, file->name);
#ifdef BONUS
	ft_printf(1, TC_YEL "%s -> " TC_NRM , file->name);
#else
	ft_printf(1, "%s -> ", file->name);
#endif
	len = readlink(path, target, sizeof(target));
	if (len < 0)
	{
		ft_printf(2, "readlink error: %s\n", strerror(errno));
		return ;
	}
	target[len] = '\0';
#ifdef BONUS
	ft_print_colors(target, &file->stat, flags);
#else
	ft_printf(1, "%s\n", target);
	(void)flags;
#endif
}

void	ft_print_time(struct stat *statbuf)
{
	char	*formatted_time;
	time_t	current_time;
	char	current_time_str[26];
	char	file_year[5];
	char	current_year[5];

	current_time = time(NULL);
	ft_strcpy(current_time_str, ctime(&current_time));
	formatted_time = ctime(&statbuf->st_mtime);
	formatted_time[16] = '\0';
	ft_printf(1, "%s ", formatted_time + 4);
}

void	ft_print_file(t_fileinfo *file, struct stat *statbuf, t_flags flags)
{
	struct passwd	*pwd;
	struct group	*grp;

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
			if (pwd == NULL)
				ft_printf(1, "%d ", statbuf->st_uid);
			else
				ft_printf(1, "%s ", pwd->pw_name);
		}
		grp = getgrgid(statbuf->st_gid);
		if (grp == NULL)
			ft_printf(1, "%d ", statbuf->st_gid);
		else
			ft_printf(1 ,"%s ", grp->gr_name);
		if (S_ISCHR(statbuf->st_mode) || S_ISBLK(statbuf->st_mode))
			ft_printf(1, "%d, %d ", major(statbuf->st_rdev), minor(statbuf->st_rdev));
		else
			ft_printf(1, "%ld ", statbuf->st_size);
		ft_print_time(statbuf);
		if (S_ISLNK(statbuf->st_mode))
			ft_print_sbl(file, flags);
#ifdef BONUS
		else
			ft_print_colors(file->name, statbuf, flags);
#else
		else
			ft_printf(1, "%s\n", file->name);
#endif
	}
#ifdef BONUS
	else
		ft_print_colors(file->name, &file->stat, flags);
#else
	else
		ft_printf(1, "%s", file->name);
#endif
}

