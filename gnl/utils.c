/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas-e <alucas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:54:39 by alucas-e          #+#    #+#             */
/*   Updated: 2025/02/19 14:54:43 by alucas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = (unsigned char)c;
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total_size;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	total_size = nmemb * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, total_size);
	return (ptr);
}

char	*ft_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (*str == (char)c)
		return ((char *)str);
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	const char	*start;

	start = str;
	while (*str)
		str++;
	return (str - start);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str_return;
	int		length;
	int		i;
	int		j;

	length = ft_strlen(s1) + ft_strlen(s2) + 1;
	str_return = NULL;
	str_return = ft_calloc(length, sizeof(char));
	if (!str_return)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str_return[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		str_return[i++] = s2[j++];
	str_return[i] = 0;
	return (str_return);
}
