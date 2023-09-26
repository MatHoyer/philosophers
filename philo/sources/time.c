/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:14:54 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/26 10:01:19 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_start(void)
{
	struct timeval	curent;
	long long		c_time;

	gettimeofday(&curent, NULL);
	c_time = (curent.tv_sec * 1000) + (curent.tv_usec / 1000);
	return (c_time);
}

long long	get_pgrm_time(t_philo *philo)
{
	struct timeval	curent;
	long long		c_time;

	gettimeofday(&curent, NULL);
	c_time = (curent.tv_sec * 1000) + (curent.tv_usec / 1000);
	return (c_time - philo->simu->time_start);
}

int	ft_usleep(long long time_in_ms, t_philo *philo)
{
	long long	start_time;

	start_time = get_pgrm_time(philo);
	while ((get_pgrm_time(philo) - start_time) < time_in_ms && !is_end(philo))
		usleep(50);
	return (0);
}
