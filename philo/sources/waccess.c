/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waccess.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:06:29 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/20 13:47:11 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_waccess(t_philo *philo)
{
	long long	time_ret;

	pthread_mutex_lock(&philo->perm->mutex_time);
	time_ret = get_pgrm_time(philo->perm->time_start);
	pthread_mutex_unlock(&philo->perm->mutex_time);
	return (time_ret);
}

t_bool	is_done_eatingwaccess(t_philo *philo)
{
	t_bool	return_data;

	return_data = false;
	pthread_mutex_lock(&philo->perm->mutex_access);
	if (philo->perm->done_eating == philo->simu.number_of_philosophers)
		return_data = true;
	pthread_mutex_unlock(&philo->perm->mutex_access);
	return (return_data);
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
	int	value;

	value = is_end_waccess(philo);
	if (!value || value == philo->num)
	{
		pthread_mutex_lock(&philo->perm->mutex_print);
		print_state(philo);
		pthread_mutex_unlock(&philo->perm->mutex_print);
	}
}

t_bool	modif_or_cmp_waccess(t_philo *philo, t_state state, t_test wanted)
{
	t_bool	return_data;

	return_data = false;
	if (wanted == TEST_CMP)
	{
		pthread_mutex_lock(&philo->perm->mutex_access);
		if (philo->state == state)
			return_data = true;
		pthread_mutex_unlock(&philo->perm->mutex_access);
	}
	else if (TEST_MOD)
	{
		pthread_mutex_lock(&philo->perm->mutex_access);
		philo->state = state;
		pthread_mutex_unlock(&philo->perm->mutex_access);
	}
	return (return_data);
}
