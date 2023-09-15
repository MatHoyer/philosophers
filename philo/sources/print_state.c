/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:29:35 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/15 12:43:18 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_state(t_philo **philo)
{
	if ((*philo)->state != (*philo)->mem_state)
	{
		(*philo)->mem_state = (*philo)->state;
		return (1);
	}
	return (0);
}

void	ft_print_state(t_philo *philo)
{
	if (philo->state == STATE_DIED)
		printf("\x1b[91m%ld %d died\x1b[0m\n", get_pgrm_time(philo->simu.time_start),
			philo->num);
	else if (philo->state == STATE_THINKING)
		printf("\x1b[93m%ld %d is thinking\x1b[0m\n", get_pgrm_time(philo->simu.time_start),
			philo->num);
	else if (philo->state == STATE_FORK)
		printf("%ld %d has taken a fork\n",
			get_pgrm_time(philo->simu.time_start), philo->num);
	else if (philo->state == STATE_FORK_BIS)
		printf("%ld %d has taken neightbor fork\n",
			get_pgrm_time(philo->simu.time_start), philo->num);
	else if (philo->state == STATE_EATING)
		printf("\x1b[92m%ld %d is eating\x1b[0m\n", get_pgrm_time(philo->simu.time_start),
			philo->num);
	else if (philo->state == STATE_SLEEPING)
		printf("\x1b[94m%ld %d is sleeping\x1b[0m\n", get_pgrm_time(philo->simu.time_start),
			philo->num);
}

t_philo	*print_state(t_philo *philo)
{
	if (check_state(&philo))
		ft_print_state(philo);
	return (philo);
}