/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 09:43:32 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/04 11:30:37 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->simu->stop)
	{
		pthread_mutex_lock(&philo->mutex_print);
		print_state(philo);
		pthread_mutex_unlock(&philo->mutex_print);
		if (philo->nb_eat == philo->simu->end_if)
		{
			philo->simu->stop = true;
		}
		if (philo->state == STATE_THINKING /*&& philo->neighbour_fork->is_up
			&& philo->his_fork.is_up*/)
		{
			pthread_mutex_lock(&philo->his_fork.mutex);
			pthread_mutex_lock(&philo->neighbour_fork->mutex);
			philo->his_fork.is_up = false;
			philo->neighbour_fork->is_up = false;
			philo->state = STATE_FORK;
			pthread_mutex_lock(&philo->mutex_print);
			print_state(philo);
			pthread_mutex_unlock(&philo->mutex_print);
			philo->state = STATE_EATING;
			philo->last_eat = get_pgrm_time(philo->simu->time_start);
		}
		if (philo->state == STATE_EATING
			&& get_pgrm_time(philo->simu->time_start)
			- philo->last_eat >= (unsigned long)philo->simu->time_to_eat)
		{
			philo->his_fork.is_up = true;
			philo->neighbour_fork->is_up = true;
			pthread_mutex_unlock(&philo->his_fork.mutex);
			pthread_mutex_unlock(&philo->neighbour_fork->mutex);
			philo->nb_eat ++;
			philo->state = STATE_THINKING;
			philo->last_eat = get_pgrm_time(philo->simu->time_start);
		}
		if (get_pgrm_time(philo->simu->time_start) - philo->last_eat >= (unsigned long)philo->simu->time_to_die)
		{
			philo->state = STATE_DIED;
		}
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
