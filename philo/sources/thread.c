/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:30:45 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/25 09:55:13 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_thread(t_philo *philo, t_simu simu)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&simu.mutex_access);
	while (++i < simu.number_of_philosophers)
	{
		if (pthread_create(&philo[i].thread, NULL, ft_thread, &philo[i]) != 0)
			return (1);
	}
	pthread_mutex_unlock(&simu.mutex_access);
	i = -1;
	while (++i < simu.number_of_philosophers)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (1);
	}
	return (0);
}