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

//cette fonction, si tu mets mode = 0; ça compte la position du premier \n dans la string
//si y'en a pas, ça renvoie -1;
//
//en mode = 1; c'est juste un strlen

int				has_n(char *str, int mode)
{
	int i;

	i = 0;
	if (mode == 0)
	{
		while (str[i] && str[i] != '\n')
			i++;
		if (str[i] == '\n')
			return (i);
		return (-1);
	}
	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}

// un strjoin qui free la chaine initiale

char			*join_and_free(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;
	char	*tmp;

	tmp = s1;
	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (has_n(s1, 1) + has_n(s2, 1) + 1));
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

//si t'as une chaine de caractere aaaaaaaaaa\nbbbb;
//ça va metre un \0 a la place du n, donc la chaine sera aaaaaaaa
//et les bbbbb seront mis dans le reste

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

int				init_and_error(int fd, char **line, char *buffer)
{
	if (line == NULL || BUFFER_SIZE <= 0 || fd <= -1 || fd >= 255)
		return (-1);
	if (!(*line = malloc(sizeof(char) * 1)))
		return (-1);
	*line[0] = 0;
	buffer[0] = 0;
	return (0);
}

//en gros : on vérifie avec le != 42 si c'est le premier appel pour ce buffer la; la valeur 42 est arbitraire
//si c'est le premier call on initie les trucs comme il faut'
//
// pour l'algo, on strjoin la line avec le reste, puis on join la line avec ce qu'on lit dans le fichier tant que y'a pas de \n dedans
// a la fin, on met le 0 dans la line au premier \n trouvé, et ce qui suit ce premier \n est mis dans le reste.
// si y'avait un \n dans la line, faut renvoyer 1 (d'ou le k =)

int				get_next_line(int fd, char **line)
{
	static char		remains[256][BUFFER_SIZE + 2];
	char			buffer[BUFFER_SIZE + 1];
	int				i;
	int				k;

	if (init_and_error(fd, line, buffer) == -1)
		return (-1);
	if (remains[fd][BUFFER_SIZE + 1] != 42)
	{
		remains[fd][0] = 0;
		remains[fd][BUFFER_SIZE + 1] = 42;
	}
	else
		*line = join_and_free(*line, remains[fd]);
	while ((has_n(*line, 0) == -1) && (i = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[i] = 0;
		*line = join_and_free(*line, buffer);
	}
	k = has_n(*line, 0);
	set_zero_and_remains(*line, remains[fd]);
	if (k == -1 || fd == -1 || i == -1)
		remains[fd][BUFFER_SIZE + 1] = 0;
	return ((i == -1 || fd == -1) ? -1 : k != -1);
}
