/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 09:31:21 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/26 09:50:49 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_fork(t_philo *philo)
{
	if (philo->num % 2)
	{
		pthread_mutex_lock(&philo->his_fork.fork);
		pthread_mutex_lock(&philo->neighbour_fork->fork);
	}
	else
	{
		pthread_mutex_lock(&philo->neighbour_fork->fork);
		pthread_mutex_lock(&philo->his_fork.fork);
	}	
	return (0);
}

int	reset_fork(t_philo *philo)
{
	if (philo->num % 2 == 0)
	{
		pthread_mutex_unlock(&philo->his_fork.fork);
		pthread_mutex_unlock(&philo->neighbour_fork->fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->neighbour_fork->fork);
		pthread_mutex_unlock(&philo->his_fork.fork);
	}	
	return (0);
}
