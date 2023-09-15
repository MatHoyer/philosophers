/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 09:43:32 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/15 13:58:02 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	is_done_eating_waccess(t_philo *philo)
{
	t_bool return_data;

	return_data = false;
	pthread_mutex_lock(&philo->perm->mutex_access);
	if (philo->perm->done_eating == philo->simu.number_of_philosophers)
		return_data = true;
	pthread_mutex_unlock(&philo->perm->mutex_access);
	return (return_data);
}

int	check_end_if(t_philo *philo)
{
	if (philo->nb_eat >= philo->simu.end_if && philo->simu.end_if != -1)
	{
		pthread_mutex_lock(&philo->perm->mutex_access);
		philo->perm->done_eating++;
		philo->nb_eat = -1;
		pthread_mutex_unlock(&philo->perm->mutex_access);
	}
	if (is_done_eating_waccess(philo))
	{
		pthread_mutex_lock(&philo->perm->mutex_access);
		philo->perm->stop = true;
		pthread_mutex_unlock(&philo->perm->mutex_access);
		return (1);
	}
	return (0);
}

t_bool	is_end_waccess(t_philo *philo)
{
	t_bool	is_end;

	if (check_end_if(philo))
	{
		pthread_mutex_lock(&philo->perm->mutex_print);
		print_state(philo);
		pthread_mutex_unlock(&philo->perm->mutex_print);
	}
	pthread_mutex_lock(&philo->perm->mutex_access);
	is_end = philo->perm->stop;
	pthread_mutex_unlock(&philo->perm->mutex_access);
	return (is_end);
}

void	print_waccess(t_philo *philo)
{
	if (!is_end_waccess(philo))
	{
		pthread_mutex_lock(&philo->perm->mutex_print);
		print_state(philo);
		pthread_mutex_unlock(&philo->perm->mutex_print);
	}
}

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

void	check_for_eating(t_philo *philo)
{
	if (modif_or_cmp_waccess(philo, STATE_THINKING, TEST_CMP)
		&& !is_end_waccess(philo))
	{
		pthread_mutex_lock(&philo->his_fork);
		modif_or_cmp_waccess(philo, STATE_FORK, TEST_MOD);
		print_waccess(philo);
		pthread_mutex_lock(philo->neighbour_fork);
		modif_or_cmp_waccess(philo, STATE_FORK_BIS, TEST_MOD);
		print_waccess(philo);
		modif_or_cmp_waccess(philo, STATE_EATING, TEST_MOD);
		philo->start_eat = get_pgrm_time(philo->simu.time_start);
		print_waccess(philo);
	}
}

void	check_for_sleeping(t_philo *philo)
{
	if (modif_or_cmp_waccess(philo, STATE_EATING, TEST_CMP)
		&& get_pgrm_time(philo->simu.time_start)
		- philo->start_eat >= (unsigned long)philo->simu.time_to_eat
		&& !is_end_waccess(philo))
	{
		pthread_mutex_unlock(philo->neighbour_fork);
		pthread_mutex_unlock(&philo->his_fork);
		if (philo->nb_eat != -1)
			philo->nb_eat++;
		modif_or_cmp_waccess(philo, STATE_SLEEPING, TEST_MOD);
		philo->last_eat = get_pgrm_time(philo->simu.time_start);
		print_waccess(philo);
	}
}

void	check_for_thinking(t_philo *philo)
{
	if (modif_or_cmp_waccess(philo, STATE_SLEEPING, TEST_CMP)
		&& get_pgrm_time(philo->simu.time_start)
		- philo->last_eat >= (unsigned long)philo->simu.time_to_sleep
		&& !is_end_waccess(philo))
	{
		modif_or_cmp_waccess(philo, STATE_THINKING, TEST_MOD);
		print_waccess(philo);
	}
}

void	check_for_die(t_philo *philo)
{
	if (get_pgrm_time(philo->simu.time_start)
		- philo->last_eat >= (unsigned long)philo->simu.time_to_die
		&& !is_end_waccess(philo))
	{
		pthread_mutex_lock(&philo->perm->mutex_access);
		philo->state_bf_die = philo->state;
		pthread_mutex_unlock(&philo->perm->mutex_access);
		modif_or_cmp_waccess(philo, STATE_DIED, TEST_MOD);
		print_waccess(philo);
		pthread_mutex_lock(&philo->perm->mutex_access);
		philo->perm->stop = true;
		pthread_mutex_unlock(&philo->perm->mutex_access);
	}
}

void	*ft_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->num % 2 != 0)
		usleep((philo->simu.time_to_eat * 1000) / 2);
	while (!is_end_waccess(philo))
	{
		check_for_eating(philo);
		check_for_sleeping(philo);
		check_for_thinking(philo);
		check_for_die(philo);
		if (philo->simu.number_of_philosophers % 2)
			usleep(philo->simu.time_to_eat * 1000);
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
	while (++i <= philo[0].simu.number_of_philosophers)
	{
		pthread_mutex_lock(&philo[0].perm->mutex_access);
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
		else if ((philo[i - 1].state != STATE_EATING && i != 1) || (philo[philo[0].simu.number_of_philosophers].state == STATE_EATING && i == 1))
			pthread_mutex_destroy(&philo[i].his_fork);
		pthread_mutex_unlock(&philo[0].perm->mutex_access);
		if (pthread_join(philo[i].thread, NULL) != 0)
			return ;
	}
}
