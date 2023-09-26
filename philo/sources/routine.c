/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:36:17 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/26 15:10:32 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_alone(t_philo *philo)
{
	print_state(philo, FORK);
	usleep(philo->simu->time_to_die * 1000);
}

int	do_eat(t_philo *philo)
{
	if (is_end(philo))
		return (1);
	if (set_fork(philo))
		return (1);
	print_state(philo, FORK);
	print_state(philo, FORK);
	print_state(philo, EAT);
	pthread_mutex_lock(&philo->simu->mutex_stop);
	philo->last_eat = get_pgrm_time(philo);
	pthread_mutex_unlock(&philo->simu->mutex_stop);
	if (ft_usleep(philo->simu->time_to_eat, philo))
		return (reset_fork(philo), 1);
	return (0);
}

int	do_sleep(t_philo *philo)
{
	if (is_end(philo))
		return (reset_fork(philo), 1);
	if (philo->nb_eat != -1)
		philo->nb_eat++;
	is_done_eating(philo);
	if (reset_fork(philo))
		return (1);
	print_state(philo, SLEEP);
	if (ft_usleep(philo->simu->time_to_sleep, philo))
		return (1);
	return (0);
}

int	absol(int value)
{
	if (value < 0)
		return (-value);
	return (value);
}

void	should_sleep(t_philo *philo, int compl )
{
	if (philo->simu->number_of_philosophers % 2 && compl <= 10)
		ft_usleep(philo->simu->time_to_eat, philo);
	else
		usleep(20);
}

void	*ft_thread(void *arg)
{
	t_philo	*philo;

	int compl ;
	philo = (t_philo *)arg;
	if (philo->simu->number_of_philosophers == 1)
		return (do_alone(philo), NULL);
	compl = absol(philo->simu->time_to_die - philo->simu->time_to_eat * 3);
	if (philo->num % 2 == 0)
		usleep(100);
	while (is_end(philo) == 0)
	{
		if (do_eat(philo) || do_sleep(philo))
			return (NULL);
		print_state(philo, THINK);
		should_sleep(philo, compl );
	}
	return (NULL);
}
