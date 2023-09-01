/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 09:43:32 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/01 10:25:40 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_thread(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	while (!philo->simu->stop)
	{
		print_state(philo);
		if (philo->state == STATE_THINKING && philo->neighbour_fork->is_up
			&& philo->his_fork.is_up)
		{
			philo->state = STATE_EATING;
			philo->his_fork.is_up = false;
			philo->neighbour_fork->is_up = false;
			philo->last_eat = get_pgrm_time(philo->simu->time_start);
		}
		if (philo->state == STATE_EATING
			&& get_pgrm_time(philo->simu->time_start)
			- philo->last_eat >= (unsigned long)philo->simu->time_to_eat)
		{
			philo->his_fork.is_up = true;
			philo->neighbour_fork->is_up = true;
			philo->state = STATE_THINKING;
			philo->last_eat = get_pgrm_time(philo->simu->time_start);
		}
		if (get_pgrm_time(philo->simu->time_start) - philo->last_eat >= (unsigned long)philo->simu->time_to_die)
		{
			philo->state = STATE_DIED;
		}
			i++;
	}
	return (NULL);
}

void	create_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (++i <= philo[0].simu->number_of_philosophers)
	{
		if (pthread_create(&philo[i].thread, NULL, ft_thread, &philo[i]) != 0)
			exit(1);
	}
	i = 0;
	while (++i <= philo[0].simu->number_of_philosophers)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			exit(1);
	}
}
