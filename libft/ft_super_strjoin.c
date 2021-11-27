/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_super_strjoin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tommy <tommy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 19:39:22 by tomartin          #+#    #+#             */
/*   Updated: 2021/09/28 18:35:55 by tommy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
static void	gestion_free(char *s1, char *s2, int str_free)
{
	if (str_free == 0)
		;
	else if (str_free == 1)
		free(s1);
	else if (str_free == 2)
		free(s2);
	else if (str_free == 3)
	{
		free(s1);
		free(s2);
	}
}

// Implementation ft_split plus add free()
// if str_free = 0 (no free)
// str_free = 1 (free s1)
// str_free = 2 (free s2)
// str_free = 3 (free s1 and s2)
char	*ft_super_strjoin(char *s1, char *s2, int str_free)
{
	int		i;
	int		j;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	p = malloc(i + 1);
	if (!p)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j] != '\0')
	{
		p[j] = s1[j];
		j++;
	}
	while (s2[i] != '\0')
		p[j++] = s2[i++];
	p[j] = '\0';
	gestion_free(s1, s2, str_free);
	return (p);
}
