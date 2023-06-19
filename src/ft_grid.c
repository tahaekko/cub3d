#include "cub3d.h"

void	ft_draw_square(t_data *data, int xpos, int ypos, int color, int size)
{
	int	tmp_col = color;

	for (int i = 0; i < size;i++)
	{
		for(int j = 0; j < size; j++)
		{
			if ((j + 1) == size || (i + 1) == size)
				color = 0;
			ft_put_pix(i + xpos, j+ypos, color, data);
			color = tmp_col;
		}
	}
}

void	ft_background(t_data *data)
{
	for(int	i= 0; i < WIDTH ;i++)
		for(int j =0; j < HEIGHT; j++)
			ft_put_pix(i, j , 0x00, data);
}
