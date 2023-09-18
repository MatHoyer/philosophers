/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 09:43:32 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/18 13:38:18 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	*ft_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->num % 2 != 0)
		usleep((philo->simu.time_to_eat * 1000) / 2);
	else
		usleep(1000);
	while (!is_end_waccess(philo))
	{
		check_for_eating(philo);
		check_for_sleeping(philo);
		check_for_thinking(philo);
		check_for_die(philo);
		if (philo->simu.number_of_philosophers % 2)
		{
			usleep(philo->simu.time_to_eat);
			pthread_mutex_lock(&philo->perm->mutex_time);
			philo->perm->time_start += philo->simu.time_to_eat / 1000;
			pthread_mutex_unlock(&philo->perm->mutex_time);
		}
	}
	return (NULL);
}

void	end_th(t_philo *philo, int i, t_philo main)
{
	while (++i <= main.simu.number_of_philosophers)
	{
		pthread_mutex_lock(&main.perm->mutex_access);
		if (philo[i].state == STATE_FORK || philo[i].state_bf_die == STATE_FORK)
		{
			pthread_mutex_unlock(philo[i].neighbour_fork);
			pthread_mutex_unlock(&philo[i].his_fork);
			pthread_mutex_destroy(&philo[i].his_fork);
		}
		else if (philo[i].state == STATE_EATING
			|| philo[i].state_bf_die == STATE_EATING)
		{
			pthread_mutex_unlock(philo[i].neighbour_fork);
			pthread_mutex_destroy(philo[i].neighbour_fork);
			pthread_mutex_unlock(&philo[i].his_fork);
			pthread_mutex_destroy(&philo[i].his_fork);
		}
		else if ((philo[main.simu.number_of_philosophers].state == STATE_EATING
				|| (philo[i - 1].state != STATE_EATING && i != 1)) && i == 1)
			pthread_mutex_destroy(&philo[i].his_fork);
		pthread_mutex_unlock(&philo[0].perm->mutex_access);
		if (pthread_join(philo[i].thread, NULL) != 0)
			return ;
	}
}

void	create_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (++i <= philo[0].simu.number_of_philosophers)
	{
		if (pthread_create(&philo[i].thread, NULL, ft_thread, &philo[i]) != 0)
			return ;
	}
	i = 1;
	while (!is_end_waccess(&philo[i]))
	{
		if (i == philo[0].simu.number_of_philosophers)
			i = 1;
		i++;
	}
	i = 0;
	end_th(philo, i, philo[0]);
}
