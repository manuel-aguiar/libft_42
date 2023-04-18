/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:01:02 by manuel            #+#    #+#             */
/*   Updated: 2023/03/11 15:01:02 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*new;

	if (!*set)
		return (ft_strdup(s1));
	if (!s1)
		return (NULL);
	while (*s1 && in_set(*s1, set))
		s1++;
	len = ft_strlen(s1);
	while (*s1 && in_set(s1[len - 1], set))
		len--;
	new = malloc(sizeof(*new) * (len + 1));
	if (new)
	{
		ft_memcpy(new, s1, len);
		new[len] = '\0';
	}
	return (new);
}
