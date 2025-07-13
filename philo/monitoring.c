/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oobbad <oobbad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:36:34 by oobbad            #+#    #+#             */
/*   Updated: 2025/07/13 14:21:13 by oobbad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_number_of_meals(t_philo *philo, int *counter)
{
	if (philo->data->number_of_eats != -1
		&& philo->counter >= philo->data->number_of_eats)
		(*counter)++;
	pthread_mutex_unlock(&philo->mutex_of_time);
	if (philo->data->number_of_eats != -1
		&& *counter >= philo->data->number_of_philosophers)
	{
		pthread_mutex_lock(&philo->data->mutex_end_simulation);
		philo->data->end_simulation = true;
		pthread_mutex_unlock(&philo->data->mutex_end_simulation);
		return (true);
	}
	return (false);
}

void	monitoring(t_data *data, int counter, int i)
{
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->philosophers[i].mutex_of_time);
		if (data->time_to_die < (get_tm()
				- data->philosophers[i].last_time_to_eat))
		{
			pthread_mutex_lock(&data->mutex_end_simulation);
			data->end_simulation = true;
			pthread_mutex_unlock(&data->mutex_end_simulation);
			print_stat(DIED, &data->philosophers[i], 1);
			pthread_mutex_unlock(&data->philosophers[i].mutex_of_time);
			return ;
		}
		if (check_number_of_meals(&data->philosophers[i], &counter))
			return ;
		i++;
		i = (i % data->number_of_philosophers);
		if (i == 0)
			counter = 0;
		if (i == 0)
			usleep(1000);
	}
}
