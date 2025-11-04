/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:28:15 by ggomes-v          #+#    #+#             */
/*   Updated: 2024/11/07 13:32:02 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	count_words(char const *str, char c)
{
	unsigned int	i;
	unsigned int	counter;

	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			counter++;
			while (str[i] != c && str[i] != '\0')
			{
				i++;
			}
		}
		else
			i++;
	}
	return (counter);
}

static char	*save_words(const char *s, char c)
{
	char	*str;
	int		n;
	int		i;

	n = 0;
	while (s[n] != '\0' && s[n] != c)
		n++;
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static	char	*if_null(char **array, int a)
{
	array[a] = NULL;
	return (*array);
}

static void	*free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		i;

	array = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s != '\0')
		{
			array[i] = save_words(s, c);
			if (array[i] == NULL)
				return (free_array(array));
			i++;
			if (c == '\0')
				if_null(array, i);
			while (*s && *s != c)
				s++;
		}
	}
	array[i] = NULL;
	return (array);
}
/*
int	main(void)
{
	int i = 0;
	char	**tabstr;
	if (!(tabstr = ft_split("   elit. Sed non risus. Suspendisse   ", ' ')))
		printf("NULL");
	else
	{
		while (tabstr[i] != NULL)
		{
			printf("%s\n", tabstr[i]);
			free(tabstr[i]);
			i++;
		}
	}
	free(tabstr);
	tabstr = NULL;
	return(0);
}
*/
