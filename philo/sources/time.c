/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:14:54 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/22 12:39:22 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_pgrm_time(long long pgrm_start)
{
	struct timeval	curent;
	long long		c_time;

	gettimeofday(&curent, NULL);
	c_time = (curent.tv_sec * 1000) + (curent.tv_usec / 1000);
	return (c_time - pgrm_start);
}
