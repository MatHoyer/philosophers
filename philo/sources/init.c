/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:53:38 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/22 13:44:25 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_static_data(t_simu *simu, int ac, char **av)
{
	simu->end_if = -1;
	simu->number_of_philosophers = ft_atoi(av[1]);
	if (simu->number_of_philosophers <= 0)
		return (printf("Error : Bad number of philo (%s).\n", av[1]));
	simu->time_to_die = ft_atoi(av[2]);
	if (simu->time_to_die <= 0)
		return (printf("Error : Bad time to life (%s).\n", av[2]));
	simu->time_to_eat = ft_atoi(av[3]);
	if (simu->time_to_eat <= 0)
		return (printf("Error : Bad time to eat (%s).\n", av[3]));
	simu->time_to_sleep = ft_atoi(av[4]);
	if (simu->time_to_sleep <= 0)
		return (printf("Error : Bad time to sleep (%s).\n", av[4]));
	if (ac == 6)
	{
		simu->end_if = ft_atoi(av[5]);
		if (simu->end_if <= 0)
			return (printf("Error : Bad number of lunch (%s).\n", av[5]));
	}
	simu->time_start = get_pgrm_time(0);
	return (0);
}

int	init_data(t_simu *simu)
{
	simu->stop = 0;
	simu->done_eating = 0;
	if (pthread_mutex_init(&simu->mutex_access, NULL)
		|| pthread_mutex_init(&simu->mutex_print, NULL))
		return (printf("Error: Bad mutex.\n"), 1);
	return (0);
}

int	init_philo(t_philo *philo, t_simu *simu_main, int i)
{
	philo->num = i + 1;
	philo->nb_eat = 0;
	philo->last_eat = 0;
	philo->his_fork.status = 0;
	philo->simu = simu_main;
	if (pthread_mutex_init(&philo->his_fork.fork, NULL)
		|| pthread_mutex_init(&philo->his_fork.access, NULL))
		return (printf("Error: Bad fork.\n"), 1);
	return (0);
}

t_philo	*init(t_philo *philo, t_simu *simu_main, int ac, char **av)
{
	int i;

	if (init_static_data(simu_main, ac, av) || init_data(simu_main))
		return (NULL);
	philo = malloc(sizeof(t_philo) * simu_main->number_of_philosophers);
	if (!philo)
		return (NULL);
	i = -1;
	while (++i < simu_main->number_of_philosophers)
	{
		if (init_philo(&philo[i], simu_main, i))
			return (NULL);
	}
	i = -1;
	while (++i < simu_main->number_of_philosophers)
	{
		if (i != simu_main->number_of_philosophers - 1)
			philo[i].neighbour_fork = &philo[i + 1].his_fork;
		else
			philo[i].neighbour_fork = &philo[0].his_fork;
	}
	return (philo);
}