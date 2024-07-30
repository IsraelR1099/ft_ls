/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:19:34 by irifarac          #+#    #+#             */
/*   Updated: 2024/07/29 20:38:22 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdarg.h>
# include <time.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <errno.h>
# include <string.h>

//Structs

enum e_filetype
{
	ft_unknown,
	ft_fifo,
	ft_chr,
	ft_dir,
	ft_blk,
	ft_reg,
	ft_lnk,
	ft_sock,
	ft_wht
};

enum	e_valid
{
	valid_flag,
	not_valid_flag,
	file
};

enum	e_time_type
{
	time_mtime,		/* default */
	time_atime,		/* -u */
	time_numtypes	/* number of elements of this enum */
};
typedef struct flags
{
	bool			long_format;	/* -l */
	bool			recurs;			/* -R */
	bool			hidden_files;	/* -a */
	bool			reverse;		/* -r */
	bool			sort_mtime;		/* -t */
	bool			sort_atime;		/* -u */
	bool			print_owner;	/* -g */
	bool			no_sort;		/* -f */
	bool			list_direc;		/* -d */
	enum e_time_type	time_type;
}	t_flags;

/* name: name of the file
 * linkname: Symlink name, name of the file linked to, otherwise NULL
 * filetype: type of file
 * linkok: For symbolic link and color printing, true if the link is valid
 * linkmode: file mode for symbolic link, st_mode of the file linked to
 */

typedef struct fileinfo
{
	enum e_filetype		filetype;
	const char			*name;
	char				*linkname;
	struct stat			stat;
	bool				linkok;
	mode_t				linkmode;
	struct fileinfo		*next;
}		t_fileinfo;

typedef struct directory
{
	enum e_filetype		filetype;
	const char			*name;
	struct stat			stat;
	struct fileinfo		*files;
	struct directory	*next;
}		t_directory;

typedef struct entry
{
	enum e_filetype		filetype;
}		t_entry;

// Flags
void			ft_parse(int argc, char **argv, t_fileinfo **files, t_directory **dir);
enum e_valid	ft_flags(const char *argv);
void		ft_parse_flags(int argc, char **argv, t_flags *flags);

// Get info
void			ft_getinfo(t_fileinfo **files);

// Print data
//void			ft_print_data(t_fileinfo *files, t_flags flags);
void			ft_print_data(t_fileinfo *files, t_directory *dir, t_flags flags);

//Utils
int				ft_find(char **pstr, char *estr, char *tokens);
void			ft_sort_files(t_fileinfo **files, t_flags flags);
void			ft_sort_dir(t_directory **dir, t_flags flags);
t_directory		*ft_build_dir(t_directory *file, struct stat statbuf, const char *name);
t_fileinfo		*ft_build_fileinfo(t_fileinfo *file, struct stat statbuf, const char *name);
void			ft_free_fileinfo(t_entry *fileinfo);

// Error
void			ft_panic(t_fileinfo *fileinfo);
#endif
