/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 17:44:21 by anmakhov          #+#    #+#             */
/*   Updated: 2026/05/28 18:15:29 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t numbers_of_ellements, size_t element_size)
{
	char	*pointer;
	size_t	iter;

	iter = 0;
	if (element_size > __SIZE_MAX__ / numbers_of_ellements)
		return (NULL);
	pointer = malloc(numbers_of_ellements * element_size);
	if (!pointer)
		return (NULL);
	while (iter < numbers_of_ellements * element_size)
	{
		pointer[iter] = 0;
		iter++;
	}
	return (pointer);
}

int	get_count(char *str)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n' && !in_word)
		{
			count++;
			in_word = 1;
		}
		else if (*str == ' ' || *str == '\t' || *str == '\n')
			in_word = 0;
		str++;
	}
	return (count);
}

void	free_all(char **arr)
{
	int	iter;

	iter = 0;
	while (arr[iter])
	{
		free(arr[iter]);
		iter++;
	}
	free(arr);
}

char	*fill_words(char *str)
{
	int		len;
	int		iter;
	char	*word;

	len = 0;
	while (str[len] && str[len] != ' ' && str[len] != '\t' && str[len] != '\n')
		len++;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	iter = 0;
	while (iter < len)
	{
		word[iter] = str[iter];
		iter++;
	}
	word[iter] = '\0';
	return (word);
}

char	**ft_split(char *str)
{
	int		size;
	int		iter;
	char	**res;

	size = get_count(str);
	iter = 0;
	res = ft_calloc((size + 1), sizeof(char *));
	if (!res)
		return (NULL);
	while (*str)
	{
		while (*str == ' ' || *str == '\t' || *str == '\n')
			str++;
		if (!*str)
			break ;
		res[iter] = fill_words(str);
		if (!res[iter])
			return (free_all(res), NULL);
		iter++;
		while (*str && *str != ' ' && *str != '\t' && *str != '\n')
			str++;
	}
	res[iter] = NULL;
	return (res);
}
