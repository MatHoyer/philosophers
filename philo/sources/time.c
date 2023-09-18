/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:33:09 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/18 11:56:00 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long get_pgrm_time(unsigned long start)
{
	struct timeval	curent;
	unsigned long	c_time;
	
	gettimeofday(&curent, NULL);
	c_time = (curent.tv_sec * 1000) + (curent.tv_usec / 1000);
	return (c_time - start);
}