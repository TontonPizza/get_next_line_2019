/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 20:56:38 by vo-nguye          #+#    #+#             */
/*   Updated: 2019/10/31 20:56:38 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

unsigned int	ft_strlen(const char *str)
{
	unsigned int i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*join_and_free(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;
	char	*tmp;

	tmp = s1;
	i = 0;
	j = 0;
	res = (char *)malloc((ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1)
						 * sizeof(char));
	if (res == 0)
		return (0);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	free(tmp);
	return (res);
}



void			set_zero_and_remains(char *line, char *remains)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
	{
		line[i] = 0;
		i++;
		while (line[j + i])
		{
			remains[j] = line[i + j];
			j++;
		}
	}
	remains[j] = 0;

}

int				has_n(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (i);
	return (-1);
}


int				get_next_line(int fd, char **line)
{
	static char		remains[BUFFER_SIZE * 2 + 2];
	char			buffer[BUFFER_SIZE + 1];
	int				i;
	int k;

	buffer[0] = 0;
	*line = malloc(sizeof(char) * 1);
	*line[0] = 0;
	if (remains[BUFFER_SIZE * 2 + 1] != 42)
	{
		remains[0] = 0;
		remains[BUFFER_SIZE * 2 + 1 ] = 42;
	}
	else
		*line = join_and_free(*line, remains);
	while ((has_n(*line) == -1) && (i = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[i] = 0;
		*line = join_and_free(*line, buffer);
	}
	k = has_n(*line);
	set_zero_and_remains(*line, remains);
	if (k == -1 || fd == -1 || i == -1)
		remains[BUFFER_SIZE * 2 + 1] = 0;
	return ((i == -1 || fd == -1)? -1 : k != -1);
}
