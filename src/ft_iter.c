/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:26:20 by israel            #+#    #+#             */
/*   Updated: 2024/08/19 21:15:22 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include "ft_printf.h"
#include "libft.h"

void	ft_print_file_bonus(t_fileinfo *files, t_flags flags, size_t max_len, size_t n_files)
{
	struct winsize			ws;
	int				num_columns;
	int				num_rows;
	int				row;
	int				col;
	t_fileinfo			*tmp;
	t_fileinfo			*current;

	if (!files)
		return ;
	tmp = files;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) < 0)
	{
		ft_printf(2, "ioctl error: %s\n", strerror(errno));
		ft_panic(NULL);
	}
	num_columns = ws.ws_col / (max_len + 1);
	if (num_columns == 0)
		num_columns = 1;
	num_rows = (n_files + num_columns - 1) / num_columns;
	for (row = 0; row < num_rows; row++)
	{
		tmp = files;
		for (col = 0; col < num_columns; col++)
		{
			int index = row + col * num_rows;
			int current_index = 0;

			current = tmp;
			while (current_index < index && current)
			{
				current = current->next;
				current_index++;
			}
			if (current)
			{
				ft_print_file(current, &tmp->stat, flags);
				if (col < num_columns - 1)
				{
					for (size_t space = ft_strlen(current->name); space <= max_len; space++)
						write(1, " ", 1);
				}
			}
		}
		write(1, "\n", 1);
	}
}

void	ft_iter_file(t_fileinfo *files, t_flags flags, size_t max_len, size_t n_files)
{
	t_fileinfo		*tmp;

	if (!files)
		return ;
#ifdef BONUS
	if (flags.long_format == false)
		ft_print_file_bonus(files, flags, max_len, n_files);
	else
	{
		tmp = files;
		while (tmp)
		{
			ft_print_file(tmp, &tmp->stat, flags);
			if (flags.long_format == false)
				write(1, " ", 1);
			tmp = tmp->next;
		}
	}
#else
	tmp = files;
	while (tmp)
	{
		ft_print_file(tmp, &tmp->stat, flags);
		if (flags.long_format == false)
			write(1, " ", 1);
		tmp = tmp->next;
	}
	(void)max_len;
	(void)n_files;
#endif
}
