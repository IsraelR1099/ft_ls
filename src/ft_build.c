/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:04:58 by israel            #+#    #+#             */
/*   Updated: 2024/07/10 12:24:06 by irifarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "libft.h"

t_fileinfo	*ft_build_fileinfo(const char *name)
{
	t_fileinfo	*fileinfo;

	fileinfo = (t_fileinfo *)malloc(sizeof(t_fileinfo));
	if (fileinfo == NULL)
		exit (1);
	ft_memset(fileinfo, 0, sizeof(t_fileinfo));
	fileinfo->name = name;
	return (fileinfo);
}
