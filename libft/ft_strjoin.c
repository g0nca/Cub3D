/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:15:21 by ggomes-v          #+#    #+#             */
/*   Updated: 2024/11/06 13:30:36 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str1;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str1 = (char *) malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str1)
		return (NULL);
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
/*
int	main(void)
{
	const char str1[] = "";
	const char str2[] = "";
	
	printf("%s\n", ft_strjoin(str1, str2));
	return(0);
}
*/
