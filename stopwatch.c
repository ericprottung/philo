/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stopwatch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:13:49 by eprottun          #+#    #+#             */
/*   Updated: 2025/11/10 16:50:43 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_end(t_philosopher *philo, int reason)
{
	long long print_time;

	pthread_mutex_lock(&philo->shared->output);
	philo->shared->death = 1;
	if (reason == DEATH)
	{
		usleep(0);
		print_time = ft_get_current_time() - philo->shared->start_time;
		printf("%lld %d died\n", print_time, philo->id);
	}
	pthread_mutex_unlock(&philo->shared->output);
}

static int	is_end(t_shared *shared, t_philosopher *philo)
{
	pthread_mutex_lock(&philo->meal_info);
	if (ft_get_current_time() - philo->last_meal > shared->time_to_die)
	{
		ft_end(philo, DEATH);
		return (pthread_mutex_unlock(&philo->meal_info), YES);
	}
	else if (shared->meal_amount != -1 && philo->meal_count >= shared->meal_amount)
	{
		ft_end(philo, 0);
		return (pthread_mutex_unlock(&philo->meal_info), YES);
	}
	return (pthread_mutex_unlock(&philo->meal_info), NO);
}

static int	end_check(t_shared *shared, t_philosopher *philo)
{
	size_t			iter;

	iter = 0;
	while (iter < shared->total_philos)
	{
		if (is_end(shared, &philo[iter]) == YES)
			return (DEATH);
		iter++;
	}
	return (0);
}

void	stopwatch(t_shared *shared, t_philosopher *philo)
{
	while (1)
	{
		if (end_check(shared, philo) == DEATH)
			break;
		usleep(2000);
	}
}