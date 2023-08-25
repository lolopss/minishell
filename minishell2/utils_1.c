/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldaniel <ldaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 08:49:06 by abougy            #+#    #+#             */
/*   Updated: 2023/08/25 13:21:17 by ldaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcomp(char *s1, char *s2)
{
	int	i;

	if (!s2)
		return (0);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_strcompn(char *s1, char *s2, int n)
{
	int	i;

	if (!s2)
		return (0);
	while(s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	char	*ret;
	int		i;
	int		j;

	i = -1;
	j = -1;
	len = ft_strlen(s1) + ft_strlen(s2);
	ret = malloc(sizeof(char) * len + 1);
	while (s1[++i])
		ret[i] = s1[i];
	while (s2[++j])
		ret[i++] = s2[j];
	ret[len] = 0;
	return (ret);
}
