/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:43:39 by mhoyer            #+#    #+#             */
/*   Updated: 2023/06/21 13:50:52 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo philo, int i)
{
	philo.num = i;
	philo.last_eat = 0;
	if (philo.num == 0)
	{
		philo.state = "vide";
		philo.mem_state = "vide";
		return ;
	}
	philo.state = "thinking";
	philo.mem_state = "thinking";
}

void	init_simu(t_simu *simu, int ac, char **av)
{
	simu->number_of_philosophers = ft_atoi(av[1]);
	if (simu->number_of_philosophers == -1)
		exit(printf("Error : Nombre de philosophes invalide (%s).\n", av[1]));
	simu->time_to_die = ft_atoi(av[2]);
	if (simu->time_to_die == -1)
		exit(printf("Error : Temps de vie invalide (%s).\n", av[2]));
	simu->time_to_eat = ft_atoi(av[3]);
	if (simu->time_to_eat == -1)
		exit(printf("Error : Temps pour manger invalide (%s).\n", av[3]));
	simu->time_to_sleep = ft_atoi(av[4]);
	if (simu->time_to_sleep == -1)
		exit(printf("Error : Temps pour dormir invalide (%s).\n", av[4]));
	if (ac == 6)
	{
		simu->end_if = ft_atoi(av[5]);
		if (simu->number_of_philosophers == -1)
			exit(printf("Error : Nombre de repas invalide (%s).\n", av[5]));
	}
}

void	init(t_simu *simu, int ac, char **av)
{
	int	i;

	i = -1;
	init_simu(simu, ac, av);
	simu->philo = malloc(sizeof(t_philo)
		* (simu->number_of_philosophers + 1));
	if (!simu->philo)
		exit(printf("Error : Mauvaise allocation des philosophes.\n"));
	while (++i <= simu->number_of_philosophers)
		init_philo(simu->philo[i], i);
}
