/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:24:33 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/23 21:01:15 by msamhaou         ###   ########.fr       */
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

void	ft_vect_draw(t_vertex *a, t_vertex *b, int color, t_data *data)
{
	double	i;
	double	*hypo;
	double	deg;
	double	adj;
	double	x;
	double	y;

	i = 0;
	hypo = ft_hypo_calc(a, b);
	x = 0;
	y = 0;
	while (i < hypo[0])
	{
		ft_put_pix((int)a->x + x, (int)a->y - y, color, data);
		if (b->x < a->x)
			x -= cos(hypo[1]);
		else
			x+= cos(hypo[1]);
		y += sin(hypo[1]);
		i++;
	}
}
