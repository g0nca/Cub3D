/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:15:58 by ggomes-v          #+#    #+#             */
/*   Updated: 2024/11/20 15:09:29 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str1;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	str1 = (char *) malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str1)
		return (NULL);
	str1 = ft_strjoin_second(s1, s2, str1);
	free(s1);
	return (str1);
}

char	*ft_strjoin_second(char *s1, char *s2, char *str1)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		str1[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str1[i + j] = s2[j];
		j++;
	}
	str1[i + j] = '\0';
	return (str1);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str && str[i] != (char)c)
	{
		if (!str[i])
			return (NULL);
		i++;
	}
	return ((char *)&str[i]);
}
