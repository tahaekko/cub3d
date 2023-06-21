/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:24:33 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/21 22:52:11 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	*ft_hypo_calc(t_vertex *a, t_vertex *b)
{
	double	*hypo;
	double	x;
	double	y;
	double	deg;

	x = (b->x - a->x);
	y = (a->y - b->y);
	hypo = malloc(sizeof(double) * 2);
	printf("x %f\n",x);
	printf("y %f\n", y);
	hypo[0] = sqrt(pow(x, 2) + pow(y, 2));
	hypo[1] = asin(y / hypo[0]);
	return (hypo);
}

void	ft_swap_vect(t_vertex **a, t_vertex **b)
{
	t_vertex	**tmp;

	tmp = a;
	*a = *b;
	*b = *tmp;
}

void	ft_vect_draw(t_vertex *a, t_vertex *b, t_data *data)
{
	double	i;
	double	*hypo;
	double	deg;
	double	adj;
	double	x;
	double	y;

	i = 0;
	hypo = ft_hypo_calc(a, b);
 	printf("c %f\n" , cos(hypo[1]));
	printf("s %f\n" , sin(hypo[1]));
	printf("hyp %f\n" , hypo[0]);
	x = 0;
	y = 0;
	while (i < hypo[0])
	{
		ft_put_pix(a->x + x, a->y - y, 0x00FF00, data);
		if (b->x < a->x)
			x -= cos(hypo[1]);
		else
			x+= cos(hypo[1]);
		y += sin(hypo[1]);
		i++;
	}
}
