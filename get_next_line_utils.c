/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajordan- <ajordan-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 10:12:58 by ajordan-          #+#    #+#             */
/*   Updated: 2021/10/20 10:05:53 by ajordan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*	---------
*	GET_LINE
*	---------
*	Extracts the line (ending in either line break and `\0` or only `\0` in EOF)
*	from static variable.
*	PARAMETERS
*	#1. The pointer to the cumulative static variable from previous runs of get_next_line.
*	RETURN VALUES
*	The string with the full line ending in a line break (`\n`) + (`\0`).
*	-------------
*	NEW_LEFT_STR
*	-------------
*	Stores in the cumulative static variable the new updated variable with whatever
*	is left from the original, minus the line extracted.
*	PARAMETERS
*	#1. The pointer to the cumulative static variable from previous runs of get_next_line.
*	RETURN VALUES
*	The new updated string with whatever is left from the original static, minus the
*	line extracted.
*/

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{	
	// On cherche si le char c est dans la chaine de caractères s
	int	i;

	i = 0;
	// Cas pas de chaine
	if (!s)
		return (0);
	// Cas caractère fin de string -> renvoie la taille de la string 
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	
	// On boucle tant qu'on arrive pas à la fin
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *left_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	// Si on a pas de left string -> on défini left_str = "";
	if (!left_str)
	{
		left_str = (char *)malloc(1 * sizeof(char));
		left_str[0] = '\0';
	}
	// Si y a rien dans les deux qu'est ce que tu fous la (!left_str redondant)
	if (!left_str || !buff)
		return (NULL);

	// On malloc la taille des 2 str +1 (pour "\0")
	str = malloc(sizeof(char) * ((ft_strlen(left_str) + ft_strlen(buff)) + 1));
	// Si malloc échoue
	if (str == NULL)
		return (NULL);

	// On ajoute 1 à 1 les caractères dans str depuis left_str puis depuis buffer
	i = -1;
	j = 0;
	if (left_str)
		while (left_str[++i] != '\0')
			str[i] = left_str[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];

	// On ajoute le "\0" à la fin et free left_str mais pas buffer qui sera réutilisé 
	// buff est free dans ft_read_to_left_str
	str[ft_strlen(left_str) + ft_strlen(buff)] = '\0';
	free(left_str);
	return (str);
}

char	*ft_get_line(char *left_str)
{
	// On sait qu'il y a un "\n" (grace à ft_str_chr) dans la ligne et on veut la récupérer
	int		i;
	char	*str;

	i = 0;
	if (!left_str[i])
		return (NULL);
	// Boucle pour compter l'indice du "\n" et malloc cette taille
	while (left_str[i] && left_str[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2)); // malloc +2 pour "\n\0"
	if (!str)  // si le malloc fail
		return (NULL);
	i = 0;
	// Boucle pour remplir la str qui vient d'être malloc
	while (left_str[i] && left_str[i] != '\n')
	{
		str[i] = left_str[i];
		i++;
	}
	// On ajoute les les deux derniers caractères
	if (left_str[i] == '\n')
	{
		str[i] = left_str[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_new_left_str(char *left_str)
{
	// Enregistre ce qu'il reste du buffer après le \n
	int		i;
	int		j;
	char	*str;
	// On parcourt le buffer jusqu'au \n
	i = 0;
	while (left_str[i] && left_str[i] != '\n')
		i++;
	// On free s'il n'y a plus rien
	if (!left_str[i])
	{
		free(left_str);
		return (NULL);
	}
	// on malloc la taille restantedu buffer 
	str = (char *)malloc(sizeof(char) * (ft_strlen(left_str) - i + 1));
	if (!str)
		return (NULL);
	i++;
	// On remplit le left_str avec la fin du buffer
	j = 0;
	while (left_str[i])
		str[j++] = left_str[i++];
	// On rajoute le \0
	str[j] = '\0';
	free(left_str);
	return (str);
}
