/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waccess.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:06:29 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/18 13:08:39 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	time_waccess(t_philo *philo)
{
	unsigned long	time_ret;

	pthread_mutex_lock(&philo->perm->mutex_time);
	time_ret = get_pgrm_time(philo->perm->time_start);
	pthread_mutex_unlock(&philo->perm->mutex_time);
	return (time_ret);
}

t_bool	is_done_eating_waccess(t_philo *philo)
{
	t_bool	return_data;

	return_data = false;
	pthread_mutex_lock(&philo->perm->mutex_access);
	if (philo->perm->done_eating == philo->simu.number_of_philosophers)
		return_data = true;
	pthread_mutex_unlock(&philo->perm->mutex_access);
	return (return_data);
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
	if (is_done_eating_waccess(philo))
	{
		pthread_mutex_lock(&philo->perm->mutex_access);
		philo->perm->stop = true;
		pthread_mutex_unlock(&philo->perm->mutex_access);
		return (1);
	}
	return (0);
}

t_bool	is_end_waccess(t_philo *philo)
{
	t_bool	is_end;

	if (check_end_if(philo))
	{
		pthread_mutex_lock(&philo->perm->mutex_print);
		print_state(philo);
		pthread_mutex_unlock(&philo->perm->mutex_print);
	}
	pthread_mutex_lock(&philo->perm->mutex_access);
	is_end = philo->perm->stop;
	pthread_mutex_unlock(&philo->perm->mutex_access);
	return (is_end);
}

void	print_waccess(t_philo *philo)
{
	if (!is_end_waccess(philo))
	{
		pthread_mutex_lock(&philo->perm->mutex_print);
		print_state(philo);
		pthread_mutex_unlock(&philo->perm->mutex_print);
	}
}
