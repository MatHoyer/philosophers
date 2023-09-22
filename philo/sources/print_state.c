/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:14:23 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/22 13:19:26 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, char *state)
{
	if (is_end(philo) && is_end(philo) != philo->num)
		return ;
	pthread_mutex_lock(&philo->simu->mutex_print);
	printf("%lld %d %s", get_pgrm_time(philo->simu->time_start), philo->num,
		state);
	pthread_mutex_unlock(&philo->simu->mutex_print);
}
