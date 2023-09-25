/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waccess.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:40:03 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/25 09:58:43 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_die(t_philo *philo)
{
	if (get_pgrm_time(philo->simu->time_start)
		- philo->last_eat > philo->simu->time_to_die)
	{
		pthread_mutex_lock(&philo->simu->mutex_access);
		philo->simu->stop = philo->num;
		pthread_mutex_unlock(&philo->simu->mutex_access);
	}
}

int	is_end(t_philo *philo)
{
	int	value;

	pthread_mutex_lock(&philo->simu->mutex_access);
	value = philo->simu->stop;
	pthread_mutex_unlock(&philo->simu->mutex_access);
	return (value);
}

int	set_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->his_fork.fork);
	pthread_mutex_lock(&philo->his_fork.access);
	philo->his_fork.status = 1;
	pthread_mutex_unlock(&philo->his_fork.access);
	is_die(philo);
	if (is_end(philo))
	{
		print_state(philo, DIE);
		pthread_mutex_unlock(&philo->his_fork.fork);
		return (1);
	}
	pthread_mutex_lock(&philo->neighbour_fork->fork);
	pthread_mutex_lock(&philo->neighbour_fork->access);
	philo->neighbour_fork->status = 1;
	pthread_mutex_unlock(&philo->neighbour_fork->access);
	return (0);
}

int	reset_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->neighbour_fork->fork);
	pthread_mutex_lock(&philo->neighbour_fork->access);
	philo->neighbour_fork->status = 0;
	pthread_mutex_unlock(&philo->neighbour_fork->access);
	is_die(philo);
	if (is_end(philo))
	{
		print_state(philo, DIE);
		return (1);
	}
	pthread_mutex_unlock(&philo->his_fork.fork);
	pthread_mutex_lock(&philo->his_fork.access);
	philo->his_fork.status = 0;
	pthread_mutex_unlock(&philo->his_fork.access);
	return (0);
}

int	test_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->his_fork.access);
	pthread_mutex_lock(&philo->neighbour_fork->access);
	while (philo->his_fork.status == 1 || philo->neighbour_fork->status == 1)
	{
		pthread_mutex_unlock(&philo->neighbour_fork->access);
		pthread_mutex_unlock(&philo->his_fork.access);
		is_die(philo);
		if (is_end(philo))
		{
			print_state(philo, DIE);
			return (1);
		}
		pthread_mutex_lock(&philo->his_fork.access);
		pthread_mutex_lock(&philo->neighbour_fork->access);
	}
	pthread_mutex_unlock(&philo->neighbour_fork->access);
	pthread_mutex_unlock(&philo->his_fork.access);
	return (0);
}
