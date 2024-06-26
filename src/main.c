/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:29:26 by irifarac          #+#    #+#             */
/*   Updated: 2024/06/26 13:40:38 by irifarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

static void	ft_getopt(t_flags *flags, const char *str_flag)
{
	printf("str flag es %s\n", str_flag);
	while (*str_flag)
	{
		if (*str_flag == 'l')
			flags->long_format = true;
		else if (*str_flag == 'R')
			flags->recurs = true;
		else if (*str_flag == 'a')
			flags->hiden_files = true;
		else if (*str_flag == 'r')
			flags->reverse = true;
		else if (*str_flag == 't')
			flags->sort_time = true;
		else if (*str_flag == 'g')
			flags->print_owner = true;
		else if (*str_flag == 'f')
			flags->no_sort = true;
		str_flag++;
	}
}

static void	ft_init(int argc, char **argv, t_fileinfo *file)
{
	int	i;
	int	j;

	if (argc == 1)
		return ;
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (*argv && argv[i][j])
		{
			if (j == 0 && argv[i][j] == '-')
				ft_getopt(&file->flags, argv[i]);
			else if (j != 0 && argv[i][j] == '-')
			{
				printf("ls: invalid option");
				exit (2);
			}
			else
				file->name = argv[i];
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	//int			i;
	//int			j;
	t_fileinfo	file;

	//i = 0;
	ft_memset(&file, 0, sizeof(file));
	ft_init(argc, argv, &file);
	printf("name es %s\n", file.name);
	/*while (i < argc)
	{
		printf("hola argc: %d and argv[i]: %s\n", i, argv[i]);
		printf("strlen: %lu\n", ft_strlen(argv[i]));
		printf("i es %d\n", i);
		j = 0;
		while (argv[i] && argv[i][j])
		{
			printf("hola argc j: %d and argv[j]: %c\n", j, argv[i][j]);
			j++;
		}
		i++;
	}*/
	return (0);
}
