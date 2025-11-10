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

int	initialisation(t_shared		*shared, t_philosopher	*philo)
{
	size_t	iter;

	iter = 0;
	shared->start_time = ft_get_current_time();
	shared->death = 0;
	pthread_mutex_init(&shared->output, NULL);
	while (iter < shared->total_philos)
	{
		pthread_mutex_init(&shared->forks[iter], NULL);
		pthread_mutex_init(&philo[iter].meal_info, NULL);
		philo[iter].shared = shared;
		philo[iter].id = iter;
		iter++;
	}
	return (0);
}

int	cleanup(t_shared *shared, t_philosopher *philo)
{
	size_t	iter;

	iter = 0;
	while (iter < shared->total_philos)
	{
		pthread_join(shared->threads[iter], NULL);
		iter++;
	}
	pthread_mutex_destroy(&shared->output);
	iter = 0;
	while (iter < shared->total_philos)
	{
		pthread_mutex_destroy(&philo[iter].meal_info);
		pthread_mutex_destroy(&shared->forks[iter]);
		iter++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	size_t			iter;
	t_shared		shared;
	t_philosopher	philo[1000];

	init_rules(&shared, argc, argv);
	initialisation(&shared, philo);
	iter = 0;
	while(iter < shared.total_philos)
	{
		pthread_mutex_lock(&philo[iter].meal_info);
		philo[iter].last_meal = shared.start_time;
		philo[iter].meal_count = 0;
		pthread_mutex_unlock(&philo[iter].meal_info);
		if (shared.total_philos % 2 == 0)
		{
			if (philo[iter].id % 2 == 0)
				pthread_create(&shared.threads[iter], NULL, even_total_and_id, &philo[iter]);
			else
				pthread_create(&shared.threads[iter], NULL, even_total_odd_id, &philo[iter]);
		}
		else
		{
			if (philo[iter].id == shared.total_philos - 1)
				pthread_create(&shared.threads[iter], NULL, last_id, &philo[iter]);
			else if (philo[iter].id % 2 == 0)
				pthread_create(&shared.threads[iter], NULL, odd_total_even_id, &philo[iter]);
			else
				pthread_create(&shared.threads[iter], NULL, odd_total_and_id, &philo[iter]);
		}
		iter++;
	}
	stopwatch(&shared, philo);
	cleanup(&shared, philo);
	return (0);
}
