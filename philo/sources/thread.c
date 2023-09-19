/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 09:43:32 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/19 13:17:08 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->simu.number_of_philosophers == 1)
		return (do_alone(philo), NULL);
	pthread_mutex_lock(&philo->perm->mutex_time);
	pthread_mutex_unlock(&philo->perm->mutex_time);
	if (philo->num % 2 != 0)
		usleep((philo->simu.time_to_eat * 1000) / 2);
	while (!is_end_waccess(philo))
	{
		if (do_eat(philo) || do_sleep(philo))
			return (NULL);
		modif_or_cmp_waccess(philo, STATE_THINKING, TEST_MOD);
		print_waccess(philo);
	}
	return (NULL);
}

void	end_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (++i <= philo[0].simu.number_of_philosophers)
	{
		if (modif_or_cmp_waccess(philo, STATE_DIED, TEST_CMP))
		{
			if (philo[i].state_bf_die == STATE_EATING)
			{
				pthread_mutex_destroy(&philo[i].his_fork);
				pthread_mutex_destroy(philo[i].neighbour_fork);
			}
		}
		if (pthread_join(philo[i].thread, NULL) != 0)
			return ;
	}
}

void	create_thread(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo[0].perm->mutex_time);
	while (++i <= philo[0].simu.number_of_philosophers)
	{
		if (pthread_create(&philo[i].thread, NULL, ft_thread, &philo[i]) != 0)
			return ;
	}
	pthread_mutex_unlock(&philo[0].perm->mutex_time);
	end_thread(philo);
}
