/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 09:43:32 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/19 12:39:06 by mhoyer           ###   ########.fr       */
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

void	do_alone(t_philo *philo)
{
	pthread_mutex_lock(&philo->perm->mutex_print);
	pthread_mutex_lock(&philo->perm->mutex_time);
	printf("%ld 1 has taken a fork\n",
		get_pgrm_time(philo->perm->time_start));
	usleep(philo->simu.time_to_die * 1000);
	printf("%ld 1 died\n", get_pgrm_time(philo->perm->time_start));
	pthread_mutex_unlock(&philo->perm->mutex_time);
	pthread_mutex_unlock(&philo->perm->mutex_print);
}

void	*ft_thread(void *arg)
{
	t_philo	*philo;
	unsigned long	start;

	philo = (t_philo *)arg;
	if (philo->simu.number_of_philosophers == 1)
		return(do_alone(philo), NULL);
	pthread_mutex_lock(&philo->perm->mutex_time);
	pthread_mutex_unlock(&philo->perm->mutex_time);
	if (philo->num % 2 != 0)
		usleep((philo->simu.time_to_eat * 1000) / 2);
	while (!is_end_waccess(philo))
	{
		pthread_mutex_lock(&philo->perm->mutex_protec);
		pthread_mutex_lock(&philo->his_fork);
		modif_or_cmp_waccess(philo, STATE_FORK, TEST_MOD);
		print_waccess(philo);
		pthread_mutex_lock(philo->neighbour_fork);
		modif_or_cmp_waccess(philo, STATE_FORK_BIS, TEST_MOD);
		print_waccess(philo);
		pthread_mutex_unlock(&philo->perm->mutex_protec);
		modif_or_cmp_waccess(philo, STATE_EATING, TEST_MOD);
		print_waccess(philo);
		start = time_waccess(philo);
		while (time_waccess(philo) - start < (unsigned long)philo->simu.time_to_eat)
		{
			check_for_die(philo);
			if (is_end_waccess(philo))
			{
				pthread_mutex_unlock(&philo->his_fork);
				pthread_mutex_unlock(philo->neighbour_fork);
				return (NULL);
			}
		}
		philo->nb_eat++;
		philo->last_eat = time_waccess(philo);
		modif_or_cmp_waccess(philo, STATE_SLEEPING, TEST_MOD);
		print_waccess(philo);
		pthread_mutex_unlock(&philo->his_fork);
		pthread_mutex_unlock(philo->neighbour_fork);
		start = time_waccess(philo);
		while (time_waccess(philo) - start < (unsigned long)philo->simu.time_to_sleep)
		{
			check_for_die(philo);
			if (is_end_waccess(philo))
			{
				return (NULL);
			}
		}
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
