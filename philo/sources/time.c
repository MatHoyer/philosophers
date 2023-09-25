/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:14:54 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/25 10:11:23 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_pgrm_time(long long pgrm_start)
{
	struct timeval	curent;
	long long		c_time;

	gettimeofday(&curent, NULL);
	c_time = (curent.tv_sec * 1000) + (curent.tv_usec / 1000);
	return (c_time - pgrm_start);
}

long long	time_waccess(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->simu->mutex_time);
	time = get_pgrm_time(philo->simu->time_start);
	pthread_mutex_unlock(&philo->simu->mutex_time);
	return (time);
}

void	reset_time(t_philo *philo, int add)
{
	pthread_mutex_lock(&philo->simu->mutex_time);
	philo->simu->time_start += add;
	pthread_mutex_unlock(&philo->simu->mutex_time);
}