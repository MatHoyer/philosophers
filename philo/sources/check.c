/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:07:41 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/20 13:44:53 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_for_die(t_philo *philo)
{
	if (time_waccess(philo)
		- philo->last_eat >= (long long)philo->simu.time_to_die
		&& !is_end_waccess(philo))
	{
		pthread_mutex_lock(&philo->perm->mutex_access);
		philo->perm->stop = philo->num;
		pthread_mutex_unlock(&philo->perm->mutex_access);
		modif_or_cmp_waccess(philo, STATE_DIED, TEST_MOD);
		print_waccess(philo);
	}
}

int	check_end_if(t_philo *philo)
{
	if (philo->nb_eat >= philo->simu.end_if && philo->simu.end_if != -1)
	{
		pthread_mutex_lock(&philo->perm->mutex_access);
		philo->perm->done_eating++;
		philo->nb_eat = -1;
		pthread_mutex_unlock(&philo->perm->mutex_access);
	}
	if (is_done_eatingwaccess(philo))
	{
		pthread_mutex_lock(&philo->perm->mutex_access);
		philo->perm->stop = true;
		pthread_mutex_unlock(&philo->perm->mutex_access);
		return (1);
	}
	return (0);
}

int	check_and_unlock(t_philo *philo)
{
	check_for_die(philo);
	if (is_end_waccess(philo))
	{
		pthread_mutex_unlock(&philo->his_fork);
		pthread_mutex_unlock(philo->neighbour_fork);
		return (1);
	}
	return (0);
}
