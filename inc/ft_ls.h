/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:19:34 by irifarac          #+#    #+#             */
/*   Updated: 2024/06/25 18:58:06 by israel           ###   ########.fr       */
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

enum filetype
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
/* name: name of the file
 * linkname: Symlink name, name of the file linked to, otherwise NULL
 * filetype: type of file
 * linkok: For symbolic link and color printing, true if the link is valid
 * linkmode: file mode for for symbolic link, st_mode of the file linked to
 */
typedef struct	fileinfo
{
	char		*name;
	char		*linkname;
	enum filetype	filetype;
	struct stat	stat;
	bool		linkok;
	mode_t		linkmode;
}		t_fileinfo;

//Utils
int	ft_find(char **pstr, char *estr, char *tokens);
size_t	ft_strlen(const char *str);

#endif
