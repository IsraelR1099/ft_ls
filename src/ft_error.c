/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:48:46 by israel            #+#    #+#             */
/*   Updated: 2024/07/05 09:38:46 by irifarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void	ft_panic(t_fileinfo *fileinfo)
{
	if (fileinfo)
		ft_free_fileinfo(fileinfo);
	exit(1);
}
