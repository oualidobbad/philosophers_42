/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oobbad <oobbad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:36:56 by oobbad            #+#    #+#             */
/*   Updated: 2025/07/17 13:28:44 by oobbad           ###   ########.fr       */
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

	if (ac < 5 || ac > 6)
		return (ft_putstr(2, "check Argument\n"), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_putstr(2, "malloc fail\n"), 1);
	if (parse_data(data, av) == 1)
	{
		if (!data->number_of_eats && data->flag)
			return (free(data), 0);
		return (free(data), 1);
	}
	if (creat_phiolosophers(data))
		return (1);
	all_free_and_destroy(data);
	return (0);
}
