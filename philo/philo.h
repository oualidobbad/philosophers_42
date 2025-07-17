/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oobbad <oobbad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:37:15 by oobbad            #+#    #+#             */
/*   Updated: 2025/07/17 13:27:36 by oobbad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TAKE_FORK "has taken a fork\n"
# define IS_THINKING "is thinking\n"
# define IS_SLEEPING "is sleeping\n"
# define IS_EATING "is eating\n"
# define DIED "died\n"

typedef struct s_philo
{
	long			last_time_to_eat;
	pthread_mutex_t	mutex_of_time;
	pthread_mutex_t	*forks_right;
	pthread_mutex_t	*forks_left;
	int				counter;
	pthread_t		philo;
	struct s_data	*data;
	int				id;
}					t_philo;

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_eats;
	int				flag;
	long			start_simulation;
	bool			end_simulation;
	pthread_mutex_t	mutex_end_simulation;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	*forks;
	t_philo			*philosophers;
}					t_data;

void				monitoring(t_data *data, int counter, int i);
long				ft_atoi(char *nb, int *flag);
long				get_tm(void);
void 				ft_putstr(int fd, char *str);
void				*routine_of_philosophers(void *arg);
void				ft_usleep(t_philo *philo, int time);
void				all_free(t_data *data);
bool				creat_phiolosophers(t_data *data);
int					parse_data(t_data *data, char **av);
void				print_stat(char *str, t_philo *philo, int option);
bool				allocate_forks_threads(t_data *data);
void				all_free_and_destroy(t_data *data);
#endif