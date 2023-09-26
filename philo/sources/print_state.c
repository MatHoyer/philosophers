/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:14:23 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/26 13:27:48 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->simu->mutex_print);
	printf("%lld %d %s", get_pgrm_time(philo), philo->num, DIE);
	pthread_mutex_unlock(&philo->simu->mutex_print);
}

void	print_state(t_philo *philo, char *state)
{
	pthread_mutex_lock(&philo->simu->mutex_print);
	if (!is_end(philo))
	{
		printf("%lld %d %s", get_pgrm_time(philo), philo->num, state);
	}
	pthread_mutex_unlock(&philo->simu->mutex_print);
}
