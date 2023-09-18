/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:04:50 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/18 13:08:40 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_for_eating(t_philo *philo)
{
	if (modif_or_cmp_waccess(philo, STATE_THINKING, TEST_CMP)
		&& !is_end_waccess(philo))
	{
		pthread_mutex_lock(&philo->his_fork);
		modif_or_cmp_waccess(philo, STATE_FORK, TEST_MOD);
		print_waccess(philo);
		pthread_mutex_lock(philo->neighbour_fork);
		modif_or_cmp_waccess(philo, STATE_FORK_BIS, TEST_MOD);
		print_waccess(philo);
		modif_or_cmp_waccess(philo, STATE_EATING, TEST_MOD);
		philo->start_eat = time_waccess(philo);
		print_waccess(philo);
	}
}

void	check_for_sleeping(t_philo *philo)
{
	if (modif_or_cmp_waccess(philo, STATE_EATING, TEST_CMP)
		&& time_waccess(philo)
		- philo->start_eat >= (unsigned long)philo->simu.time_to_eat
		&& !is_end_waccess(philo))
	{
		pthread_mutex_unlock(philo->neighbour_fork);
		pthread_mutex_unlock(&philo->his_fork);
		if (philo->nb_eat != -1)
			philo->nb_eat++;
		modif_or_cmp_waccess(philo, STATE_SLEEPING, TEST_MOD);
		philo->last_eat = time_waccess(philo);
		print_waccess(philo);
	}
}

void	check_for_thinking(t_philo *philo)
{
	if (modif_or_cmp_waccess(philo, STATE_SLEEPING, TEST_CMP)
		&& time_waccess(philo)
		- philo->last_eat >= (unsigned long)philo->simu.time_to_sleep
		&& !is_end_waccess(philo))
	{
		modif_or_cmp_waccess(philo, STATE_THINKING, TEST_MOD);
		print_waccess(philo);
	}
}

void	check_for_die(t_philo *philo)
{
	if (time_waccess(philo)
		- philo->last_eat >= (unsigned long)philo->simu.time_to_die
		&& !is_end_waccess(philo))
	{
		pthread_mutex_lock(&philo->perm->mutex_access);
		philo->state_bf_die = philo->state;
		pthread_mutex_unlock(&philo->perm->mutex_access);
		modif_or_cmp_waccess(philo, STATE_DIED, TEST_MOD);
		print_waccess(philo);
		pthread_mutex_lock(&philo->perm->mutex_access);
		philo->perm->stop = true;
		pthread_mutex_unlock(&philo->perm->mutex_access);
	}
}
