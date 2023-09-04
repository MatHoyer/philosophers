/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 09:43:32 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/04 16:22:42 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_end_if(t_philo *philo)
{
	pthread_mutex_lock(&philo->simu->mutex_access);
	if (philo->nb_eat == philo->simu->end_if)
		philo->simu->stop = true;
	pthread_mutex_unlock(&philo->simu->mutex_access);
}

void	check_for_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->simu->mutex_access);
	if (philo->state == STATE_THINKING)
	{
		pthread_mutex_lock(&philo->his_fork.mutex);
		pthread_mutex_lock(&philo->neighbour_fork->mutex);
		philo->state = STATE_FORK;
		pthread_mutex_lock(&philo->simu->mutex_print);
		print_state(philo);
		pthread_mutex_unlock(&philo->simu->mutex_print);
		philo->state = STATE_EATING;
		philo->last_eat = get_pgrm_time(philo->simu->time_start);
	}
	pthread_mutex_unlock(&philo->simu->mutex_access);
}

void	check_for_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->simu->mutex_access);
	if (philo->state == STATE_EATING && get_pgrm_time(philo->simu->time_start)
		- philo->last_eat >= (unsigned long)philo->simu->time_to_eat)
	{
		pthread_mutex_unlock(&philo->his_fork.mutex);
		pthread_mutex_unlock(&philo->neighbour_fork->mutex);
		philo->nb_eat++;
		philo->state = STATE_SLEEPING;
		philo->last_eat = get_pgrm_time(philo->simu->time_start);
	}
	pthread_mutex_unlock(&philo->simu->mutex_access);
}

void	check_for_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->simu->mutex_access);
	if (philo->state == STATE_SLEEPING && get_pgrm_time(philo->simu->time_start)
		- philo->last_eat >= (unsigned long)philo->simu->time_to_sleep)
	{
		philo->state = STATE_THINKING;
	}
	pthread_mutex_unlock(&philo->simu->mutex_access);
}

void	check_for_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->simu->mutex_access);
	if (get_pgrm_time(philo->simu->time_start)
		- philo->last_eat >= (unsigned long)philo->simu->time_to_die)
	{
		philo->state = STATE_DIED;
	}
	pthread_mutex_unlock(&philo->simu->mutex_access);
}

void	*ft_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (pthread_mutex_lock(&philo->simu->mutex_access) == 0 && !philo->simu->stop)
	{
		pthread_mutex_unlock(&philo->simu->mutex_access);
		check_end_if(philo);
		pthread_mutex_lock(&philo->simu->mutex_print);
		print_state(philo);
		pthread_mutex_unlock(&philo->simu->mutex_print);
		check_for_eating(philo);
		check_for_sleeping(philo);
		check_for_thinking(philo);
		check_for_die(philo);
	}
	return (NULL);
}

void	create_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (++i <= philo[0].simu->number_of_philosophers)
	{
		if (pthread_create(&philo[i].thread, NULL, ft_thread, &philo[i]) != 0)
			exit(1);
	}
	i = 0;
	while (++i <= philo[0].simu->number_of_philosophers)
	{
		pthread_mutex_destroy(&philo[i].his_fork.mutex);
		if (pthread_join(philo[i].thread, NULL) != 0)
			exit(1);
	}
}
