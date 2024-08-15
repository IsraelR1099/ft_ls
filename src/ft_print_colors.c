/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:20:33 by israel            #+#    #+#             */
/*   Updated: 2024/08/14 18:27:35 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "../inc/colors.h"
#include "ft_printf.h"

void	ft_print_colors(const char *name, struct stat *statbuf)
{
	if (S_ISDIR(statbuf->st_mode))
		ft_printf(1, TC_BLU "%s" TC_NRM "\n", name);
	else if (S_ISLNK(statbuf->st_mode))
		ft_printf(1, TC_YEL "%s" TC_NRM "\n", name);
	else if (S_ISCHR(statbuf->st_mode))
		ft_printf(1, "%s\n", name);
	else if (S_ISBLK(statbuf->st_mode))
		ft_printf(1, "%s\n", name);
	else if (S_ISFIFO(statbuf->st_mode))
		ft_printf(1, "%s\n", name);
	else if (S_ISSOCK(statbuf->st_mode))
		ft_printf(1, "%s\n", name);
	else if (statbuf->st_mode & S_IXUSR)
		ft_printf(1, "%s\n", name);
	else
		ft_printf(1, "%s\n", name);
}

