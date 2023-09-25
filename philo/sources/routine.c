/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:36:17 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/25 09:57:23 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_alone(t_philo *philo)
{
	print_state(philo, FORK);
	usleep(philo->simu->time_to_die * 1000);
	print_state(philo, DIE);
}

int	do_eat(t_philo *philo)
{
	long long	start;

	usleep(1000);
	if (set_fork(philo))
		return (1);
	print_state(philo, FORK);
	print_state(philo, FORK);
	print_state(philo, EAT);
	start = get_pgrm_time(philo->simu->time_start);
	philo->last_eat = start;
	while (get_pgrm_time(philo->simu->time_start)
		- start < (long long)philo->simu->time_to_eat)
	{
		is_die(philo);
		if (is_end(philo))
		{
			print_state(philo, DIE);
			reset_fork(philo);
			return (1);
		}
	}
	return (0);
}

int	do_sleep(t_philo *philo)
{
	long long	start;

	philo->nb_eat++;
	if (reset_fork(philo))
		return (1);
	print_state(philo, SLEEP);
	start = get_pgrm_time(philo->simu->time_start);
	while (get_pgrm_time(philo->simu->time_start)
		- start < (long long)philo->simu->time_to_sleep)
	{
		is_die(philo);
		if (is_end(philo))
		{
			print_state(philo, DIE);
			return (1);
		}
	}
	return (0);
}

int	do_think(t_philo *philo)
{
	print_state(philo, THINK);
	if (test_fork(philo))
		return (1);
	return (0);
}

void	*ft_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->simu->mutex_access);
	pthread_mutex_unlock(&philo->simu->mutex_access);
	if (philo->simu->number_of_philosophers == 1)
		return (do_alone(philo), NULL);
	if (philo->num % 2 == 0 /*|| philo->num == philo->simu->number_of_philosophers*/)
		usleep(100);
	while (!is_end(philo))
	{
		if (do_eat(philo) || do_sleep(philo) || do_think(philo))
			return (NULL);
	}
	return (NULL);
}
