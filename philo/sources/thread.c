/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 09:43:32 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/14 11:55:42 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_waccess(t_philo *philo)
{
	pthread_mutex_lock(&philo->perm->mutex_print);
	print_state(philo);
	pthread_mutex_unlock(&philo->perm->mutex_print);
}
t_bool	is_end_waccess(t_philo *philo)
{
	t_bool	is_end;

	pthread_mutex_lock(&philo->perm->mutex_access);
	is_end = philo->perm->stop;
	pthread_mutex_unlock(&philo->perm->mutex_access);
	return (is_end);
}

t_bool	modif_or_cmp_waccess(t_philo *philo, t_state state, t_test wanted)
{
	t_bool	to_return;

	to_return = false;
	if (wanted == TEST_CMP)
	{
		pthread_mutex_lock(&philo->perm->mutex_access);
		if (philo->state == state)
			to_return = true;
		pthread_mutex_unlock(&philo->perm->mutex_access);
	}
	else if (TEST_MOD)
	{
		pthread_mutex_lock(&philo->perm->mutex_access);
		philo->state = state;
		pthread_mutex_unlock(&philo->perm->mutex_access);
	}
	return (to_return);
}

void	check_end_if(t_philo *philo)
{
	if (philo->nb_eat >= philo->simu.end_if && philo->simu.end_if != -1)
	{
		pthread_mutex_lock(&philo->perm->mutex_access);
		philo->perm->stop = true;
		pthread_mutex_unlock(&philo->perm->mutex_access);
	}
}

void	check_for_eating(t_philo *philo)
{
	if (modif_or_cmp_waccess(philo, STATE_THINKING, TEST_CMP))
	{
		if (philo->num % 2 == 0
			&& get_pgrm_time(philo->simu.time_start) < (unsigned long)philo->simu.time_to_eat)
		{
			usleep(philo->simu.time_to_eat);
		}
		pthread_mutex_lock(&philo->his_fork.mutex);
		pthread_mutex_lock(&philo->neighbour_fork->mutex);
		modif_or_cmp_waccess(philo, STATE_FORK, TEST_MOD);
		print_waccess(philo);
		modif_or_cmp_waccess(philo, STATE_EATING, TEST_MOD);
		philo->start_eat = get_pgrm_time(philo->simu.time_start);
	}
}

void	check_for_sleeping(t_philo *philo)
{
	if (modif_or_cmp_waccess(philo, STATE_EATING, TEST_CMP) && get_pgrm_time(philo->simu.time_start)
		- philo->start_eat >= (unsigned long)philo->simu.time_to_eat)
	{
		pthread_mutex_unlock(&philo->neighbour_fork->mutex);
		pthread_mutex_unlock(&philo->his_fork.mutex);
		philo->nb_eat++;
		modif_or_cmp_waccess(philo, STATE_SLEEPING, TEST_MOD);
		philo->last_eat = get_pgrm_time(philo->simu.time_start);
	}
}

void	check_for_thinking(t_philo *philo)
{
	if (modif_or_cmp_waccess(philo, STATE_SLEEPING, TEST_CMP) && get_pgrm_time(philo->simu.time_start)
		- philo->last_eat >= (unsigned long)philo->simu.time_to_sleep)
	{
		modif_or_cmp_waccess(philo, STATE_THINKING, TEST_MOD);
	}
}

void	check_for_die(t_philo *philo)
{
	if (get_pgrm_time(philo->simu.time_start)
		- philo->last_eat >= (unsigned long)philo->simu.time_to_die)
	{
		modif_or_cmp_waccess(philo, STATE_DIED, TEST_MOD);
		pthread_mutex_lock(&philo->perm->mutex_access);
		philo->perm->stop = true;
		pthread_mutex_unlock(&philo->perm->mutex_access);
	}
}

void	*ft_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->num % 2 == 0 || philo->num == philo->simu.number_of_philosophers)
		usleep(philo->simu.time_to_eat * 100);
	while (!is_end_waccess(philo))
	{
		print_waccess(philo);
		check_for_eating(philo);
		check_for_sleeping(philo);
		check_for_thinking(philo);
		check_end_if(philo);
		check_for_die(philo);
	}
	return (NULL);
}

void	create_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (++i <= philo[0].simu.number_of_philosophers)
	{
		print_waccess(&philo[i]);
		if (pthread_create(&philo[i].thread, NULL, ft_thread, &philo[i]) != 0)
			exit(1);
	}
	i = 0;
	while (++i <= philo[0].simu.number_of_philosophers)
	{
		pthread_mutex_lock(&philo[0].perm->mutex_access);
		if (philo[i].state == STATE_EATING)
		{
			pthread_mutex_unlock(&philo[i].neighbour_fork->mutex);
			pthread_mutex_unlock(&philo[i].his_fork.mutex);
			pthread_mutex_destroy(&philo[i].neighbour_fork->mutex);
			pthread_mutex_destroy(&philo[i].his_fork.mutex);
		}
		else if (philo[0].simu.number_of_philosophers == 1
				|| (i != philo[0].simu.number_of_philosophers && i != 1 && philo[i + 1].state != STATE_EATING && philo[i - 1].state != STATE_EATING)
				|| (i == philo[0].simu.number_of_philosophers && philo[1].state != STATE_EATING && philo[i - 1].state != STATE_EATING)
				|| (i == 1 && philo[i + 1].state != STATE_EATING && philo[philo[0].simu.number_of_philosophers].state != STATE_EATING))
			pthread_mutex_destroy(&philo[i].his_fork.mutex);
		else
		{
			pthread_mutex_unlock(&philo[i].his_fork.mutex);
			pthread_mutex_destroy(&philo[i].his_fork.mutex);
		}
		pthread_mutex_unlock(&philo[0].perm->mutex_access);
		if (pthread_join(philo[i].thread, NULL) != 0)
			exit(1);
	}
}
