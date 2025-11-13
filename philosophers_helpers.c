/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:33:47 by eprottun          #+#    #+#             */
/*   Updated: 2025/11/08 13:58:49 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	return_number;

	i = 0;
	sign = 1;
	return_number = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		return_number *= 10;
		return_number += str[i] - 48;
		i++;
	}
	return_number *= (long)sign;
	return ((int)return_number);
}

void	init_rules(t_data *shared, int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		printf("./philosophers number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		exit(1);
	}
	shared->total_philos = ft_atoi(argv[1]);
	shared->time_to_die = ft_atoi(argv[2]);
	shared->eat_time = ft_atoi(argv[3]);
	shared->sleep_time = ft_atoi(argv[4]);
	if (argc >= 6)
		shared->meal_amount = ft_atoi(argv[5]);
	else
		shared->meal_amount = -1;
}

void efficient_sleep(long long duration)
{
	long long start;
	long long remaining;

	start = get_time();
	if (duration > 2)
		usleep((duration - 2) * 1000);
	while (get_time() - start < duration)
		usleep(100);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + (tv.tv_usec + 500) / 1000);
}
