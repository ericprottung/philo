/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stopwatch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:13:49 by eprottun          #+#    #+#             */
/*   Updated: 2025/11/10 10:04:41 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_end(t_shared *shared, t_philosopher philo)
{
	if (ft_get_current_time() - philo.last_meal > shared->time_to_die)
	{
		ft_end(&philo, DEATH);
		return (1);
	}
	else if (shared->meal_amount != -1 && philo.meal_count >= shared->meal_amount)
	{
		ft_end(&philo, 0);
		return (1);
	}
	return (0);
}

static int	set_flag_end_and_prio(t_shared *shared, t_philosopher *philo)
{
	size_t			iter;

	iter = 0;
	while (iter < shared->total_philos)
	{
		pthread_mutex_lock(&philo[iter].meal_info);
		if (is_end(shared, philo[iter]) == YES)
			return (pthread_mutex_unlock(&philo[iter].meal_info), DEATH);
		pthread_mutex_unlock(&philo[iter].meal_info);
		iter++;
	}
	return (0);
}

void	stopwatch(t_shared *shared, t_philosopher *philo)
{
	long long loop_time;
	long long loop_count;

	while (1)
	{
		if (set_flag_end_and_prio(shared, philo) == DEATH)
			break;
		usleep(2000);
	}
}