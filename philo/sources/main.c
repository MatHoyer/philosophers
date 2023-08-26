/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:58:27 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/26 19:54:08 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_not_enought_arg_error(int ac)
{
	if (ac < 5)
	{
		printf("\033[31mError : ./philo needs at least 5 arguments.\033[0m\n");
		printf("\033[32mLike:\033[0m");
		printf(" ./philo number_of_philosophers time_to_die ");
		printf("time_to_eat time_to_sleep\n");
		printf("\033[32mAnd optional:\033[0m");
		printf(" number_of_times_each_philosopher_must_eat\n");
	}
	else
		printf("\033[31mError : too much arguments (%d).\033[0m\n", ac);
	return (1);
}

void *fonctionDuThread(void *arg) {
    t_philo *philo = (t_philo *) arg;

	printf("%ldms %d %s\n", get_pgrm_time(philo->time_start), philo->num, philo->state);
    return NULL;
}

void	test_thread(t_simu *simu)
{
	int	i;

	i = 0;
	while (++i <= simu->number_of_philosophers)
	{
		if (pthread_create(&simu->philo[i].thread, NULL, fonctionDuThread, &simu->philo[i]) != 0)
			exit(1);
		simu->philo[i].time_start = simu->time_start;
    }
	i = 0;
	while (++i <= simu->number_of_philosophers)
	{
		if (pthread_join(simu->philo[i].thread, NULL) != 0)
			exit(1);
	}
}

int	main(int ac, char **av)
{
	t_simu	simu;

	if (ac < 5 || ac > 6)
		exit(print_not_enought_arg_error(ac));
	init(&simu, ac, av);
	test_thread(&simu);
	return (0);
}
