/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:26:20 by israel            #+#    #+#             */
/*   Updated: 2024/08/15 21:54:58 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void	ft_iter_file(t_fileinfo *files, t_flags flags, size_t max_len)
{
	t_fileinfo	*tmp;

	tmp = files;
	while (tmp)
	{
		ft_print_file(tmp, &tmp->stat, flags);
#ifdef BONUS
		if (flags.long_format == false)
			write(1, "\n", 1);
#else
		if (flags.long_format == false)
			write(1, " ", 1);
#endif
		tmp = tmp->next;
	}
	(void)max_len;
}
