/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:29:35 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/20 09:01:59 by mhoyer           ###   ########.fr       */
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
		printf("%lld %d died\n", time_waccess(philo), philo->num);
	else if (philo->state == STATE_THINKING)
		printf("%lld %d is thinking\n", time_waccess(philo), philo->num);
	else if (philo->state == STATE_FORK)
		printf("%lld %d has taken a fork\n", time_waccess(philo), philo->num);
	else if (philo->state == STATE_FORK_BIS)
		printf("%lld %d has taken a fork\n", time_waccess(philo), philo->num);
	else if (philo->state == STATE_EATING)
		printf("%lld %d is eating\n", time_waccess(philo), philo->num);
	else if (philo->state == STATE_SLEEPING)
		printf("%lld %d is sleeping\n", time_waccess(philo), philo->num);
}

t_philo	*print_state(t_philo *philo)
{
	if (check_state(&philo))
		ft_print_state(philo);
	return (philo);
}
