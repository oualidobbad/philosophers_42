/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oobbad <oobbad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:24:30 by oobbad            #+#    #+#             */
/*   Updated: 2025/07/13 10:55:09 by oobbad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handl_sign(long *sign, char c, int *i)
{
	if (c == '-' || c == '+')
	{
		if (c == '-')
			*sign = -1;
		(*i)++;
	}
}

long	ft_atoi(char *nb, int *flag)
{
	long	n;
	int		i;
	long	sign;

	n = 0;
	i = 0;
	sign = 1;
	if ((nb[i] == '-' || nb[i] == '+') && nb[i + 1] == '\0')
		*flag = 0;
	while ((nb[i] >= 9 && nb[i] <= 13) || nb[i] == 32)
		i++;
	handl_sign(&sign, nb[i], &i);
	while (nb[i] >= '0' && nb[i] <= '9')
	{
		n = n * 10 + (nb[i] - 48);
		if (n * sign > INT_MAX || n * sign < 0)
			*flag = 0;
		i++;
	}
	if (!(nb[i] >= '0' && nb[i] <= '9') && nb[i])
		*flag = 0;
	return (n * sign);
}
