/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:20:33 by israel            #+#    #+#             */
/*   Updated: 2024/08/20 21:48:31 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "../inc/colors.h"
#include "ft_printf.h"

void	ft_print_colors(const char *name, struct stat *statbuf, t_flags flags)
{
	if (S_ISDIR(statbuf->st_mode))
		ft_printf(1, TC_BLU "%s" TC_NRM, name);
	else if (S_ISLNK(statbuf->st_mode))
		ft_printf(1, TC_YEL "%s" TC_NRM, name);
	else if (S_ISCHR(statbuf->st_mode))
		ft_printf(1, TC_B_RED "%s" TC_B_NRM, name);
	else if (S_ISBLK(statbuf->st_mode))
		ft_printf(1, TC_B_GRN "%s" TC_B_NRM, name);
	else if (S_ISFIFO(statbuf->st_mode))
		ft_printf(1, "%s", name);
	else if (S_ISSOCK(statbuf->st_mode))
		ft_printf(1, "%s", name);
	else if (statbuf->st_mode & S_IXUSR)
		ft_printf(1, "%s", name);
	else
		ft_printf(1, "%s", name);
	if (flags.long_format == true)
		ft_printf(1, "\n");
}
