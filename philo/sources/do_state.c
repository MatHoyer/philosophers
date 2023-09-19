/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:04:50 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/19 13:20:41 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_alone(t_philo *philo)
{
	pthread_mutex_lock(&philo->perm->mutex_print);
	pthread_mutex_lock(&philo->perm->mutex_time);
	printf("%ld 1 has taken a fork\n", get_pgrm_time(philo->perm->time_start));
	usleep(philo->simu.time_to_die * 1000);
	printf("%ld 1 died\n", get_pgrm_time(philo->perm->time_start));
	pthread_mutex_unlock(&philo->perm->mutex_time);
	pthread_mutex_unlock(&philo->perm->mutex_print);
}

int	do_eat(t_philo *philo)
{
	unsigned long	start;

	pthread_mutex_lock(&philo->perm->mutex_protec);
	pthread_mutex_lock(&philo->his_fork);
	modif_or_cmp_waccess(philo, STATE_FORK, TEST_MOD);
	print_waccess(philo);
	pthread_mutex_lock(philo->neighbour_fork);
	modif_or_cmp_waccess(philo, STATE_FORK_BIS, TEST_MOD);
	print_waccess(philo);
	pthread_mutex_unlock(&philo->perm->mutex_protec);
	modif_or_cmp_waccess(philo, STATE_EATING, TEST_MOD);
	print_waccess(philo);
	start = time_waccess(philo);
	while (time_waccess(philo) - start < (unsigned long)philo->simu.time_to_eat)
	{
		check_for_die(philo);
		if (is_end_waccess(philo))
		{
			pthread_mutex_unlock(&philo->his_fork);
			pthread_mutex_unlock(philo->neighbour_fork);
			return (1);
		}
	}
	return (0);
}

int	do_sleep(t_philo *philo)
{
	unsigned long	start;

	philo->nb_eat++;
	philo->last_eat = time_waccess(philo);
	modif_or_cmp_waccess(philo, STATE_SLEEPING, TEST_MOD);
	print_waccess(philo);
	pthread_mutex_unlock(&philo->his_fork);
	pthread_mutex_unlock(philo->neighbour_fork);
	start = time_waccess(philo);
	while (time_waccess(philo)
		- start < (unsigned long)philo->simu.time_to_sleep)
	{
		check_for_die(philo);
		if (is_end_waccess(philo))
		{
			return (1);
		}
	}
	return (0);
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
