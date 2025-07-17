/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oobbad <oobbad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:36:39 by oobbad            #+#    #+#             */
/*   Updated: 2025/07/17 13:33:40 by oobbad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_stat(char *str, t_philo *philo, int option)
{
	long	time;

	time = get_tm() - philo->data->start_simulation;
	if (option == 1)
	{
		pthread_mutex_lock(&philo->data->mutex_print);
		printf("%ld %d %s", time, philo->id, str);
		pthread_mutex_unlock(&philo->data->mutex_print);
		return ;
	}
	pthread_mutex_lock(&philo->data->mutex_end_simulation);
	if (!philo->data->end_simulation)
	{
		pthread_mutex_lock(&philo->data->mutex_print);
		printf("%ld %d %s", time, philo->id, str);
		pthread_mutex_unlock(&philo->data->mutex_print);
	}
	pthread_mutex_unlock(&philo->data->mutex_end_simulation);
}

bool	allocate_forks_threads(t_data *data)
{
	data->philosophers = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philosophers)
		return (false);
	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	if (!data->forks)
		return (free(data->philosophers), false);
	return (true);
}

void	ft_usleep(t_philo *philo, int ms_time)
{
	unsigned long	start;
	unsigned long	us_time;

	start = get_tm() * 1000;
	us_time = (unsigned long)ms_time * 1000;
	while (((get_tm() * 1000) - start) < us_time)
	{
		pthread_mutex_lock(&philo->data->mutex_end_simulation);
		if (philo->data->end_simulation)
		{
			pthread_mutex_unlock(&philo->data->mutex_end_simulation);
			return ;
		}
		pthread_mutex_unlock(&philo->data->mutex_end_simulation);
		usleep(50);
	}
}

long	get_tm(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void ft_putstr(int fd, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(fd, str[i], 1);
		i++;
	}
}
