/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oobbad <oobbad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:36:29 by oobbad            #+#    #+#             */
/*   Updated: 2025/07/13 14:00:31 by oobbad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_data_of_philo(t_data *data)
{
	int	i;

	i = 0;
	data->end_simulation = false;
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->mutex_end_simulation, NULL);
	while (i < data->number_of_philosophers)
		pthread_mutex_init(&data->forks[i++], NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->philosophers[i].mutex_of_time, NULL);
		data->philosophers[i].id = i + 1;
		data->philosophers[i].forks_left = &data->forks[i];
		if (i == data->number_of_philosophers - 1)
			data->philosophers[i].forks_right = &data->forks[0];
		else
			data->philosophers[i].forks_right = &data->forks[i + 1];
		data->philosophers[i].last_time_to_eat = get_tm();
		data->philosophers[i].data = data;
		data->philosophers[i].counter = 0;
		i++;
	}
	return (true);
}

int	parse_data(t_data *data, char **av)
{
	data->flag = 1;
	data->number_of_eats = -1;
	data->number_of_philosophers = ft_atoi(av[1], &data->flag);
	if (data->flag == 0)
		return (write(2, "Error\n check number of philosophers\n", 37), 1);
	data->time_to_die = ft_atoi(av[2], &data->flag);
	if (data->flag == 0)
		return (write(2, "Error\n check time to die\n", 26), 1);
	data->time_to_eat = ft_atoi(av[3], &data->flag);
	if (data->flag == 0)
		return (write(2, "Error\n check time to eat\n", 26), 1);
	data->time_to_sleep = ft_atoi(av[4], &data->flag);
	if (data->flag == 0)
		return (write(2, "Error\n check time to sleep\n", 28), 1);
	if (av[5])
	{
		data->number_of_eats = ft_atoi(av[5], &data->flag);
		if (data->flag == 0)
			return (write(2, "Error\n invalid nb eats\n", 24), 1);
	}
	if (!allocate_forks_threads(data))
		return (write(2, "fail malloc\n", 13), 1);
	init_data_of_philo(data);
	return (0);
}

bool	creat_phiolosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&data->philosophers[i].philo, NULL,
				routine_of_philosophers, &data->philosophers[i]) < 0)
		{
			while (i > -1)
				pthread_join(data->philosophers[i--].philo, NULL);
			all_free_and_destroy(data);
			return (write(2, "fail pthreads create\n", 22), true);
		}
		i++;
	}
	monitoring(data, 0, 0);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->philosophers[i].philo, NULL);
		i++;
	}
	return (false);
}
