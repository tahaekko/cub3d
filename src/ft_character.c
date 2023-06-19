#include "cub3d.h"

t_rect	*ft_rect_init()
{
	t_rect *rect;

	rect = malloc(sizeof(t_rect));
	rect->height = 5;
	rect->width = 5;
	rect->xpos = 50;
	rect->ypos = 60;
	rect->ray_len = 50;
	rect->color = 0xFD15DF;
	return(rect);
}

void	ft_draw_character(t_data *data)
{
	t_rect *rect = data->rect;
	for (int i = 0; i < rect->width;i++)
		for(int j = 0; j < rect->height; j++)
			ft_put_pix(rect->xpos + i, rect->ypos + j, rect->color, data);
}
