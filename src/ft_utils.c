/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:33:06 by irifarac          #+#    #+#             */
/*   Updated: 2024/07/31 13:08:01 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "libft.h"

void	ft_free_fileinfo(t_fileinfo *fileinfo)
{
	t_fileinfo	*tmp;
	t_fileinfo	*cast;

	cast = fileinfo;
	while (cast != NULL)
	{
		tmp = cast;
		cast = cast->next;
		free((char *)tmp->name);
		free(tmp);
	}
}

void	ft_free_dir(t_directory *dir)
{
	t_directory	*tmp;
	t_directory	*cast;

	cast = dir;
	while (cast != NULL)
	{
		tmp = cast;
		cast = cast->next;
		free((char *)tmp->name);
		free(tmp);
	}
}

enum e_valid	ft_flags(const char *argv)
{
	char	*etmp;
	char	*tmp;

	if (!ft_strchr(argv, '-'))
		return (file);
	tmp = (char *)argv;
	etmp = (char *)argv + ft_strlen(argv);
	while (tmp < etmp)
	{
		if (*tmp == '-')
		{
			if (*argv == '-' && (tmp - argv) > 0)
				return (not_valid_flag);
			if (*argv != '-' && (tmp - argv) > 0)
				return (file);
		}
		tmp++;
	}
	return (valid_flag);
}
