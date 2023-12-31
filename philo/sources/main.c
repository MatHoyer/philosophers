/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:48:31 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/26 15:27:25 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	absol(int value)
{
	if (value < 0)
		return (-value);
	return (value);
}

void	end_pgrm(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo[0].simu->number_of_philosophers)
		pthread_mutex_destroy(&philo[i].his_fork.fork);
	pthread_mutex_destroy(&philo->simu->mutex_eat);
	pthread_mutex_destroy(&philo->simu->mutex_stop);
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
		return (1);
	if (create_thread(philo, &simu_main))
		return (printf("Error: Bad thread.\n"), 1);
	end_pgrm(philo);
	return (0);
}
