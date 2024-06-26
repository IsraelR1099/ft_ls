/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:19:34 by irifarac          #+#    #+#             */
/*   Updated: 2024/06/26 12:57:29 by irifarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <stdbool.h>

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

enum	e_time_type
{
	time_mtime,		/* default */
	time_atime,		/* -u */
	time_numtypes	/* number of elements of this enum */
};
/* name: name of the file
 * linkname: Symlink name, name of the file linked to, otherwise NULL
 * filetype: type of file
 * linkok: For symbolic link and color printing, true if the link is valid
 * linkmode: file mode for for symbolic link, st_mode of the file linked to
 */
typedef struct flags
{
	bool			long_format;	/* -l */
	bool			recurs;			/* -R */
	bool			hiden_files;	/* -a */
	bool			reverse;		/* -r */
	bool			sort_time;		/* -t */
	bool			print_owner;	/* -g */
	bool			no_sort;		/* -f */
	bool			list_direc;
	enum e_time_type	time_type;
}	t_flags;

typedef struct fileinfo
{
	char		*name;
	char		*linkname;
	enum e_filetype	filetype;
	struct stat	stat;
	t_flags		flags;
	bool		linkok;
	mode_t		linkmode;

}		t_fileinfo;
//Utils
int	ft_find(char **pstr, char *estr, char *tokens);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *dest, int ch, size_t count);
#endif
