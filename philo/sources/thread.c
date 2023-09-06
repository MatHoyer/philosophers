/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 09:43:32 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/06 13:46:20 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_waccess(t_philo *philo)
{
	pthread_mutex_lock(&philo->perm->mutex_print);
	print_state(philo);
	pthread_mutex_unlock(&philo->perm->mutex_print);
}

int	check_end_if(t_philo *philo)
{
	if (philo->nb_eat >= philo->simu.end_if)
	{
		pthread_mutex_lock(&philo->perm->mutex_access);
		philo->perm->stop = true;
		pthread_mutex_unlock(&philo->perm->mutex_access);
		return (1);
	}
	return (0);
}

int	check_for_eating(t_philo *philo)
{
	if (philo->state == STATE_THINKING)
	{
		pthread_mutex_lock(&philo->his_fork.mutex);
		pthread_mutex_lock(&philo->neighbour_fork->mutex);
		philo->state = STATE_FORK;
		print_waccess(philo);
		philo->state = STATE_EATING;
		philo->last_eat = get_pgrm_time(philo->simu.time_start);
		return (1);
	}
	return (0);
}

int	check_for_sleeping(t_philo *philo)
{
	if (philo->state == STATE_EATING && get_pgrm_time(philo->simu.time_start)
		- philo->last_eat >= (unsigned long)philo->simu.time_to_eat)
	{
		pthread_mutex_unlock(&philo->his_fork.mutex);
		pthread_mutex_unlock(&philo->neighbour_fork->mutex);
		philo->nb_eat++;
		philo->state = STATE_SLEEPING;
		philo->last_eat = get_pgrm_time(philo->simu.time_start);
		return (1);
	}
	return (0);
}

int	check_for_thinking(t_philo *philo)
{
	if (philo->state == STATE_SLEEPING && get_pgrm_time(philo->simu.time_start)
		- philo->last_eat >= (unsigned long)philo->simu.time_to_sleep)
	{
		philo->state = STATE_THINKING;
		return (1);
	}
	return (0);
}

int	check_for_die(t_philo *philo)
{
	if (get_pgrm_time(philo->simu.time_start)
		- philo->last_eat >= (unsigned long)philo->simu.time_to_die)
	{
		philo->state = STATE_DIED;
		return (1);
	}
	return (0);
}

void	*ft_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (pthread_mutex_lock(&philo->perm->mutex_access) == 0
		&& !philo->perm->stop && pthread_mutex_unlock(&philo->perm->mutex_access) == 0)
	{
		print_waccess(philo);
		if (check_end_if(philo))
		{}
		else if (check_for_eating(philo))
		{}
		else if (check_for_sleeping(philo))
		{}
		else if (check_for_thinking(philo))
		{}
		else if (check_for_die(philo))
		{}
		printf("%d\n", philo->simu.end_if);
	}
	return (NULL);
}

void	create_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (++i <= philo[0].simu.number_of_philosophers)
	{
		if (pthread_create(&philo[i].thread, NULL, ft_thread, &philo[i]) != 0)
			exit(1);
	}
	i = 0;
	while (++i <= philo[0].simu.number_of_philosophers)
	{
		pthread_mutex_destroy(&philo[i].his_fork.mutex);
		if (pthread_join(philo[i].thread, NULL) != 0)
			exit(1);
	}
}
