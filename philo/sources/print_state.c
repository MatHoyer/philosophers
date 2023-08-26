/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:29:35 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/26 21:48:04 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_state(t_philo **philo)
{
	if ((*philo)->state != (*philo)->mem_state)
	{
		(*philo)->mem_state = (*philo)->state;
		if ((*philo)->state == STATE_DIED)
			(*philo)->simu->stop = true;
		return (1);
	}
	return (0);
}

void	ft_print_state(t_philo philo)
{
	if (philo.state == STATE_DIED)
		printf("%ldms %d died\n", get_pgrm_time(philo.simu->time_start), philo.num);
	else if (philo.state == STATE_THINKING)
		printf("%ldms %d is thinking\n", get_pgrm_time(philo.simu->time_start), philo.num);
	else if (philo.state == STATE_FORK)
		printf("%ldms %d has taken a fork\n", get_pgrm_time(philo.simu->time_start), philo.num);
	else if (philo.state == STATE_EATING)
		printf("%ldms %d is eating\n", get_pgrm_time(philo.simu->time_start), philo.num);
	else if (philo.state == STATE_SLEEPING)
		printf("%ldms %d is sleeping\n", get_pgrm_time(philo.simu->time_start), philo.num);
}

t_philo	*print_state(t_philo *philo)
{
	if (check_state(&philo))
		ft_print_state(*philo);
	return (philo);
}