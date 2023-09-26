/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:30:45 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/26 14:33:22 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor(t_philo *philo)
{
	int		i;

	while (!is_end(philo))
	{
		i = -1;
		while (++i < philo[0].simu->number_of_philosophers)
		{
			pthread_mutex_lock(&philo[0].simu->mutex_stop);
			if (get_pgrm_time(&philo[0])
				- philo[i].last_eat > philo[0].simu->time_to_die)
			{
				philo[0].simu->stop = philo[i].num;
				pthread_mutex_unlock(&philo[0].simu->mutex_stop);
				print_death(philo);
				return ;
			}
			pthread_mutex_unlock(&philo[0].simu->mutex_stop);
		}
		usleep(20);
	}
}

int	create_thread(t_philo *philo, t_simu *simu)
{
	int i;

	i = -1;
	simu->time_start = get_start();
	while (++i < simu->number_of_philosophers)
	{
		if (pthread_create(&philo[i].thread, NULL, ft_thread, &philo[i]) != 0)
			return (1);
	}
	monitor(philo);
	i = -1;
	while (++i < simu->number_of_philosophers)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (1);
	}
	return (0);
}