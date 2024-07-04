/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:33:06 by irifarac          #+#    #+#             */
/*   Updated: 2024/07/04 20:14:52 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

static char	*ft_strchr(const char *str, int ch)
{
	int	position;

	position = 0;
	while (str[position] != '\0')
	{
		if (str[position] == (char)ch)
			return ((char *)str + position);
		position++;
	}
	if (str[position] == (char)ch)
		return ((char *)str + position);
	return (NULL);
}

void	*ft_memset(void	*dest, int ch, size_t count)
{
	unsigned int	position;
	char			*new_dest;

	new_dest = (char *)dest;
	position = 0;
	while (position < count)
	{
		new_dest[position] = (char)ch;
		position++;
	}
	return (new_dest);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

int	ft_find(char **pstr, char *estr, char *tokens)
{
	char	*tmp;

	tmp = *pstr;
	while (tmp < estr && ft_strchr("\t\r\n\v ", *tmp))
		tmp++;
	*pstr = tmp;
	return (*tmp && ft_strchr(tokens, *tmp));
}

void ft_free_fileinfo(t_fileinfo *fileinfo)
{
	t_fileinfo	*tmp;

	while (fileinfo != NULL)
	{
		tmp = fileinfo;
		fileinfo = fileinfo->next;
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
