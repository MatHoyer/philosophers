/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:14:23 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/25 11:34:48 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, char *state)
{
	int	value;

	value = is_end(philo);
	if (value == 0 || (value != 0 && value == philo->num))
	{
		pthread_mutex_lock(&philo->simu->mutex_print);
		printf("%lld %d %s", time_waccess(philo), philo->num,
			state);
		pthread_mutex_unlock(&philo->simu->mutex_print);
		if (value != 0)
		{
			pthread_mutex_lock(&philo->simu->mutex_stop);
			philo->simu->stop = -1;
			pthread_mutex_unlock(&philo->simu->mutex_stop);
		}
	}
}
