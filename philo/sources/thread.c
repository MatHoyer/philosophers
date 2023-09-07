/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 09:43:32 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/07 13:48:54 by mhoyer           ###   ########.fr       */
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
	if (philo->nb_eat >= philo->simu.end_if && philo->simu.end_if != -1)
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
		pthread_mutex_lock(&philo->perm->mutex_access);
		philo->state = STATE_EATING;
		pthread_mutex_unlock(&philo->perm->mutex_access);
		philo->start_eat = get_pgrm_time(philo->simu.time_start);
		return (1);
	}
	return (0);
}

int	check_for_sleeping(t_philo *philo)
{
	if (philo->state == STATE_EATING && get_pgrm_time(philo->simu.time_start)
		- philo->start_eat >= (unsigned long)philo->simu.time_to_eat)
	{
		pthread_mutex_unlock(&philo->neighbour_fork->mutex);
		pthread_mutex_unlock(&philo->his_fork.mutex);
		philo->nb_eat++;
		pthread_mutex_lock(&philo->perm->mutex_access);
		philo->state = STATE_SLEEPING;
		pthread_mutex_unlock(&philo->perm->mutex_access);
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
		pthread_mutex_lock(&philo->perm->mutex_access);
		philo->state = STATE_THINKING;
		pthread_mutex_unlock(&philo->perm->mutex_access);
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
		pthread_mutex_lock(&philo->perm->mutex_access);
		philo->perm->stop = true;
		pthread_mutex_unlock(&philo->perm->mutex_access);
		return (1);
	}
	return (0);
}

void	*ft_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->num % 2 == 0)
		usleep(philo->simu.time_to_eat - 10);
	while (1)
	{
		check_for_die(philo);
		print_waccess(philo);
		if (pthread_mutex_lock(&philo->perm->mutex_access) == 0
			&& !philo->perm->stop)
		{
			pthread_mutex_unlock(&philo->perm->mutex_access);
			check_for_eating(philo);
			check_for_sleeping(philo);
			check_for_thinking(philo);
			check_end_if(philo);
		}
		else
			break ;
	}
	printf("TUP");
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
		if (pthread_mutex_lock(&philo[i].perm->mutex_access) == 0 && philo[i].state == STATE_EATING)
		{
			pthread_mutex_unlock(&philo[i].perm->mutex_access);
			pthread_mutex_unlock(&philo[i].his_fork.mutex);
			pthread_mutex_unlock(&philo[i].neighbour_fork->mutex);
		}
		pthread_mutex_lock(&philo[i].his_fork.mutex);
		pthread_mutex_unlock(&philo[i].his_fork.mutex);
		pthread_mutex_destroy(&philo[i].his_fork.mutex);
		if (pthread_join(philo[i].thread, NULL) != 0)
			exit(1);
	}
}
