/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:04:50 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/20 12:10:49 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_alone(t_philo *philo)
{
	pthread_mutex_lock(&philo->perm->mutex_print);
	pthread_mutex_lock(&philo->perm->mutex_time);
	printf("%lld 1 has taken a fork\n", get_pgrm_time(philo->perm->time_start));
	usleep(philo->simu.time_to_die * 1000);
	printf("%lld 1 died\n", get_pgrm_time(philo->perm->time_start));
	pthread_mutex_unlock(&philo->perm->mutex_time);
	pthread_mutex_unlock(&philo->perm->mutex_print);
}

int	do_eat(t_philo *philo)
{
	long long	start;

	pthread_mutex_lock(&philo->his_fork);
	modif_or_cmp_waccess(philo, STATE_FORK, TEST_MOD);
	print_waccess(philo);
	pthread_mutex_lock(philo->neighbour_fork);
	modif_or_cmp_waccess(philo, STATE_FORK_BIS, TEST_MOD);
	print_waccess(philo);
	modif_or_cmp_waccess(philo, STATE_EATING, TEST_MOD);
	print_waccess(philo);
	if (check_and_unlock(philo))
		return (1);
	start = time_waccess(philo);
	philo->last_eat = start;
	while (time_waccess(philo) - start < (long long)philo->simu.time_to_eat)
	{
		if (check_and_unlock(philo))
			return (1);
	}
	return (0);
}

int	do_sleep(t_philo *philo)
{
	long long	start;

	philo->nb_eat++;
	modif_or_cmp_waccess(philo, STATE_SLEEPING, TEST_MOD);
	print_waccess(philo);
	pthread_mutex_unlock(&philo->his_fork);
	pthread_mutex_unlock(philo->neighbour_fork);
	start = time_waccess(philo);
	while (time_waccess(philo) - start < (long long)philo->simu.time_to_sleep)
	{
		check_for_die(philo);
		if (is_end_waccess(philo))
		{
			return (1);
		}
	}
	return (0);
}

int	do_think(t_philo *philo)
{
	long long	start;

	modif_or_cmp_waccess(philo, STATE_THINKING, TEST_MOD);
	print_waccess(philo);
	start = time_waccess(philo);
	while (time_waccess(philo) - start < (long long)philo->simu.time_to_eat
		- (long long)philo->simu.time_to_sleep)
	{
		check_for_die(philo);
		if (is_end_waccess(philo))
		{
			return (1);
		}
	}
	return (0);
}
