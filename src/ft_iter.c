/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:26:20 by israel            #+#    #+#             */
/*   Updated: 2024/08/16 11:11:22 by irifarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "ft_printf.h"

void	ft_iter_file(t_fileinfo *files, t_flags flags, size_t max_len, size_t n_files)
{
	t_fileinfo		*tmp;
	struct winsize	ws;
	int				num_columns;
	int				num_rows;
	int				tmp_rows;

	tmp = files;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) < 0)
	{
		ft_printf(2, "ioctl error: %s\n", strerror(errno));
		ft_panic(NULL);
	}
	printf("max len %zu y num files %zu\n", max_len, n_files);
	printf("ws info col %d y row %d\n", ws.ws_col, ws.ws_row);
	num_columns = ws.ws_col / (max_len + 1);
	num_rows = (n_files + num_columns - 1) / num_columns;
	tmp_rows = num_rows;
	printf("num rows es %d\n", num_rows);
	printf("num col %d\n", num_columns);
	while (tmp)
	{
		ft_print_file(tmp, &tmp->stat, flags);
#ifdef BONUS
		if (flags.long_format == false)
		{
			if (tmp_rows > 0)
			{
				write(1, "\n", 1);
				tmp_rows--;
			}
			if (tmp_rows == 0)
			{
				tmp_rows = num_rows;
				write(1, "\t", 1);
			}
		}
#else
		if (flags.long_format == false)
			write(1, " ", 1);
#endif
		tmp = tmp->next;
	}
	(void)max_len;
}
