/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:29:26 by irifarac          #+#    #+#             */
/*   Updated: 2024/06/25 18:45:36 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

int	main(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (i < argc)
	{
		printf("hola argc: %d and argv[i]: %s\n", i, argv[i]);
		printf("strlen: %lu\n", ft_strlen(argv[i]));
		j = 0;
		while (argv[i] && argv[i][j])
		{
			printf("hola argc j: %d and argv[j]: %c\n", j, argv[i][j]);
			j++;
		}
		i++;
	}
	return (0);
}
