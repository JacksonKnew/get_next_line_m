/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajordan- <ajordan-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 10:12:14 by ajordan-          #+#    #+#             */
/*   Updated: 2021/10/20 10:04:09 by ajordan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
*	GET_NEXT_LINE
*	-------------
*	DESCRIPTION
*	This function takes an opened file descriptor and returns its next line.
*	This function has undefined behavior when reading from a binary file.
*	PARAMETERS
*	#1. A file descriptor 
*	RETURN VALUES
*	If successful, get_next_line returns a string with the full line ending in
*	a line break (`\n`) when there is one. 
*	If an error occurs, or there's nothing more to read, it returns NULL.
*	----------------------------------------------------------------------------
*	AUXILIARY FUNCTIONS
*	-------------------
*	READ_TO_LEFT_STR
*	-----------------
*	DESCRIPTION
*	Takes the opened file descriptor and saves on a "buff" variable what readed
*	from it. Then joins it to the cumulative static variable for the persistence
*	of the information.
*	PARAMETERS
*	#1. A file descriptor.
*	#2. The pointer to the cumulative static variable from previous runs of
*	get_next_line.
*	RETURN VALUES
*	The new static variable value with buffer joined for the persistence of the info,
*	or NULL if error.
*/

#include "get_next_line.h"
#include <unistd.h>
//#include <stdio.h>
//#include <fcntl.h>

char	*ft_read_to_left_str(int fd, char *left_str)
{
	char	*buff;
	int		rd_bytes;

	// malloc le buffer
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);

	// On boucle sur les lectures du fichier tant qu'il n'y a pas de \n dans le buffer
	rd_bytes = 1;
	while (!ft_strchr(left_str, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		// Si problème
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		// On ajoute le \0 quui n'est pas dans le buffer de base
		buff[rd_bytes] = '\0';
		// On join à ce qui a déja été lu
		left_str = ft_strjoin(left_str, buff);
	}
	// Ne pas oublier de la free!
	free(buff);
	return (left_str);
}

char	*get_next_line(int fd)
{
	// line : ce qu'on va construire et renvoyer
	char		*line;
	// left_str correspond à ce qu'il restait au dernier appel de get_next_line après le \n dans le buffer
	static char	*left_str;

	// Si problème
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	// On fait autant de lectures que nécessaire pour avoir un \n
	left_str = ft_read_to_left_str(fd, left_str);
	if (!left_str)
		return (NULL);
	// maintenant qu'on sait qu'il y a un \n, on récupère jusqu'à lui
	line = ft_get_line(left_str);
	// On met dans la variable static ce qu'il y a après dans ce qui a été lu
	left_str = ft_new_left_str(left_str);
	return (line);
}

/*int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;
	fd1 = open("tests/test.txt", O_RDONLY);
	fd2 = open("tests/test2.txt", O_RDONLY);
	fd3 = open("tests/test3.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd3);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}*/
