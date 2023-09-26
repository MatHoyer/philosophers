/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waccess.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:40:03 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/26 15:25:26 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_done_eating(t_philo *philo)
{
	if (philo->nb_eat >= philo->simu->end_if && philo->simu->end_if != -1)
	{
		pthread_mutex_lock(&philo->simu->mutex_eat);
		philo->nb_eat = -1;
		philo->simu->done_eating += 1;
		if (philo->simu->done_eating == philo->simu->number_of_philosophers)
		{
			pthread_mutex_lock(&philo->simu->mutex_stop);
			philo->simu->stop = 1;
			pthread_mutex_unlock(&philo->simu->mutex_stop);
		}
		pthread_mutex_unlock(&philo->simu->mutex_eat);
	}
}

int	is_end(t_philo *philo)
{
	int	value;

	pthread_mutex_lock(&philo->simu->mutex_stop);
	value = philo->simu->stop;
	pthread_mutex_unlock(&philo->simu->mutex_stop);
	return (value);
}
