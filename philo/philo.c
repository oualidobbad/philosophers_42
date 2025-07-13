/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oobbad <oobbad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:36:56 by oobbad            #+#    #+#             */
/*   Updated: 2025/07/13 09:07:58 by oobbad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	all_free(t_data *data)
{
	free(data->philosophers);
	free(data->forks);
	free(data);
}

void	all_free_and_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philosophers[i].mutex_of_time);
		i++;
	}
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_end_simulation);
	all_free(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (write(2, "malloc fail\n", 13), 1);
	if (ac < 5 || ac > 6)
	{
		write(2, "check Argument\n", 16);
		return (1);
	}
	if (parse_data(data, av) == 1)
		return (1);
	data->start_simulation = get_tm();
	if (creat_phiolosophers(data))
		return (1);
	all_free_and_destroy(data);
	return (0);
}
