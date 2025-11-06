/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:13:19 by eprottun          #+#    #+#             */
/*   Updated: 2025/11/06 14:00:14 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

void	ft_output(t_philosopher *me, char *msg, int death_call)
{
	size_t	iter;
	long long print_time;
	
	iter = 0;
	while (iter < me->shared->total_philos)
	{
		pthread_mutex_lock(&me->shared->dead_access);
		if (me->shared->dead[iter] == 1)
		{
			pthread_mutex_unlock(&me->shared->dead_access);
			pthread_exit(NULL);
		}
		pthread_mutex_unlock(&me->shared->dead_access);
		iter++;
	}
	print_time = ft_get_current_time() - me->shared->start_time;
	pthread_mutex_lock(&me->shared->output);
	printf(msg, print_time, me->id);
	pthread_mutex_unlock(&me->shared->output);
}

void	ft_eat(t_philosopher *me)
{
	long long	start_time;

	ft_output(me, "%lld %d is eating\n", NO);
	pthread_mutex_lock(&me->shared->last_meal_access);
	me->last_meal = ft_get_current_time();
	start_time = me->last_meal;
	me->meal_count++;
	pthread_mutex_unlock(&me->shared->last_meal_access);
	while (ft_get_current_time() - start_time < me->shared->eat_time)
		usleep(2000);
}

void	ft_think(t_philosopher *me)
{
	ft_output(me, "%lld %d is thinking\n", NO);
}

void	ft_sleep(t_philosopher *me)
{
	size_t	start_time;

	ft_output(me, "%lld %d is sleeping\n", NO);
	start_time = ft_get_current_time();
	while (ft_get_current_time() - start_time < me->shared->sleep_time)
		usleep(2000);
}
