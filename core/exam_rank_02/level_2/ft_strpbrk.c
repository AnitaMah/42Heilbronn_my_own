/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 16:54:22 by anmakhov          #+#    #+#             */
/*   Updated: 2026/05/22 17:13:37 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char    *ft_strpbrk(const char *s1, const char *s2)
{
    int iter;
    int j;
    
    iter = 0;
    while (s1[iter])
    {
        j = 0;
        while (s2[j])
        {
            if (s1[iter] == s2[j])
                return ((char *) s1[iter]);
            j++;
        }
        iter++;
    }
    return (NULL);
}