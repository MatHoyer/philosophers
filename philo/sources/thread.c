/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:30:45 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/25 11:33:34 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_done_eating(t_philo *philo)
{
	if (philo->nb_eat >= philo->simu->end_if && philo->simu->end_if != -1)
	{
		pthread_mutex_lock(&philo->simu->mutex_eat);
		philo->simu->done_eating += 1;
		philo->nb_eat = -1;
		if (philo->simu->done_eating == philo->simu->number_of_philosophers)
		{
			pthread_mutex_lock(&philo->simu->mutex_stop);
			if (philo->simu->stop == 0)
				philo->simu->stop = philo->num;
			pthread_mutex_unlock(&philo->simu->mutex_stop);	
		}
		pthread_mutex_unlock(&philo->simu->mutex_eat);
	}
}

int	create_thread(t_philo *philo, t_simu simu)
{
	int i;

	i = -1;
	while (++i < simu.number_of_philosophers)
	{
		if (pthread_create(&philo[i].thread, NULL, ft_thread, &philo[i]) != 0)
			return (1);
	}
	i = -1;
	while (++i < simu.number_of_philosophers)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (1);
	}
	return (0);
}