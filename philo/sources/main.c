/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:48:31 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/22 13:04:21 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_pgrm(t_philo *philo)
{
	pthread_mutex_destroy(&philo->simu->mutex_access);
	pthread_mutex_destroy(&philo->simu->mutex_print);
	free(philo);
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_simu	simu_main;

	philo = NULL;
	if (ac < 5 || ac > 6)
		return (print_not_enought_argerror(ac));
	philo = init(philo, &simu_main, ac, av);
	if (!philo)
		return (printf("Error: Bad philo alloc.\n"), 1);
	if (create_thread(philo, simu_main))
		return (printf("Error: Bad thread.\n"), 1);
	end_pgrm(philo);
	return (0);
}