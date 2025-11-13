/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:15:45 by eprottun          #+#    #+#             */
/*   Updated: 2025/11/08 14:09:14 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_program(t_data *shared, t_philosopher *philo)
{
	size_t	iter;

	iter = 0;
	shared->death = 0;
	pthread_mutex_init(&shared->print, NULL);
	while (iter < shared->total_philos)
	{
		pthread_mutex_init(&shared->forks[iter].key, NULL);
		pthread_mutex_init(&philo[iter].meal_info, NULL);
		philo[iter].shared = shared;
		philo[iter].id = iter;
		iter++;
	}
	return (0);
}

int	cleanup(t_data *shared, t_philosopher *philo)
{
	size_t	iter;

	iter = 0;
	while (iter < shared->total_philos)
	{
		pthread_join(shared->threads[iter], NULL);
		iter++;
	}
	pthread_mutex_destroy(&shared->print);
	iter = 0;
	while (iter < shared->total_philos)
	{
		pthread_mutex_destroy(&philo[iter].meal_info);
		pthread_mutex_destroy(&shared->forks[iter].key);
		iter++;
	}
	return (0);
}

void	*lonely_philo(void *data)
{
	t_philosopher	*me;
	pthread_mutex_t	*right_fork;

	me = (t_philosopher *)data;
	right_fork = &me->shared->forks[me->id].key;
	pthread_mutex_lock(right_fork);
	if (output(me, "%lld %d has taken a fork\n", RIGHT))
		return (NULL);
	efficient_sleep(me->shared->time_to_die);
	pthread_mutex_unlock(right_fork);
	return (NULL);
}

int	even_philo_setup(t_philosopher *philo, t_data *shared)
{
	size_t	iter;

	iter = 0;
	shared->start_time = get_time() + 10;
	while (iter < shared->total_philos)
	{
		philo[iter].last_meal = shared->start_time;
		philo[iter].meal_count = 0;
		if (!(philo[iter].id & 1))
			pthread_create(&shared->threads[iter], NULL, even_total_and_id, &philo[iter]);
		else
			pthread_create(&shared->threads[iter], NULL, even_total_odd_id, &philo[iter]);
		iter++;
	}
	return (0);
}

int	lonely_philo_setup(t_philosopher *philo, t_data *shared)
{
	shared->start_time = get_time();
	philo[0].last_meal = shared->start_time;
	philo[0].meal_count = 0;
	pthread_create(&shared->threads[0], NULL, lonely_philo, &philo[0]);
	return (0);
}

int	odd_philo_setup(t_philosopher *philo, t_data *shared)
{
	size_t	iter;

	iter = 0;
	shared->start_time = get_time() + 10;
	while (iter < shared->total_philos)
	{
		philo[iter].last_meal = shared->start_time;
		philo[iter].meal_count = 0;
		if (philo[iter].id == shared->total_philos - 1)
			pthread_create(&shared->threads[iter], NULL, last_id, &philo[iter]);
		else if (!(philo[iter].id & 1))
			pthread_create(&shared->threads[iter], NULL, odd_total_even_id, &philo[iter]);
		else
			pthread_create(&shared->threads[iter], NULL, odd_total_and_id, &philo[iter]);
		iter++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data			shared;
	t_philosopher	philo[250];

	init_rules(&shared, argc, argv);
	init_program(&shared, philo);
	if (shared.total_philos == 1)
		lonely_philo_setup(philo, &shared);
	else if (shared.total_philos % 2 == 0)
		even_philo_setup(philo, &shared);
	else
		odd_philo_setup(philo, &shared);
	stopwatch(&shared, philo);
	cleanup(&shared, philo);
	return (0);
}
