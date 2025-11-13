/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stopwatch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:13:49 by eprottun          #+#    #+#             */
/*   Updated: 2025/11/13 20:51:12 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	end(t_philosopher *philo, int reason)
{
	long long	print_time;

	pthread_mutex_lock(&philo->shared->print);
	philo->shared->death = 1;
	if (reason == DEATH)
	{
		print_time = get_time() - philo->shared->start_time;
		printf("%lld %d died\n", print_time, philo->id);
	}
	if (reason == DINNER_DONE)
		printf("simulation finished!\n");
	pthread_mutex_unlock(&philo->shared->print);
}

static int	is_end(t_data *shared, t_philosopher *philo, size_t *philos_done)
{
	pthread_mutex_lock(&philo->meal_info);
	if (get_time() - philo->last_meal > shared->time_to_die)
	{
		end(philo, DEATH);
		return (pthread_mutex_unlock(&philo->meal_info), YES);
	}
	else if (shared->meal_amount != -1 && philo->meal_count >= shared->meal_amount)
	{
		(*philos_done)++;
		if (*philos_done >= shared->total_philos)
		{
			end(philo, DINNER_DONE);
			return (pthread_mutex_unlock(&philo->meal_info), YES);
		}
	}
	return (pthread_mutex_unlock(&philo->meal_info), NO);
}

static int	end_check(t_data *shared, t_philosopher *philo)
{
	size_t	iter;
	size_t	finished_philos;

	iter = 0;
	finished_philos = 0;
	while (iter < shared->total_philos)
	{
		if (is_end(shared, &philo[iter], &finished_philos) == YES)
			return (DEATH);
		iter++;
	}
	return (0);
}

void	stopwatch(t_data *shared, t_philosopher *philo)
{
	while (1)
	{
		if (end_check(shared, philo) == DEATH)
			break ;
		usleep(200);
	}
}
