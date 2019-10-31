/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 22:39:10 by vo-nguye          #+#    #+#             */
/*   Updated: 2019/10/31 22:39:10 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int fd1 = open(argv[1], O_RDONLY);
	int fd2 = open(argv[2], O_RDONLY);
	char *line;
	int k = 1;
	int j = 1;

	while (j > 0 || k > 0)
	{
		k = get_next_line(fd1, &line);
		printf("%s\n", line);
		free(line);
		j = get_next_line(fd2, &line);
		printf("%s\n", line);
		free(line);
	}


    return (argc + argv[0][0]);
}