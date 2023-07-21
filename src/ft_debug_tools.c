#include "cub3d.h"

typedef struct s_elem
{
	int				content;
	struct s_elem	*next;
}	t_elem;

static int	ft_check_exist(int *arr, int elem)
{
	// while ()
}

t_elem	*new_elem(int content)
{
	t_elem *elem = malloc(sizeof(t_elem));
	elem->content = content;
	elem->next = NULL;
	return (elem);
}

void	elem_add(t_elem **node, t_elem *back)
{
	if (!*node)
		*node = back;
	else
	{
		while ((*node)->next)
			*node = (*node)->next;
		(*node)->next = back;
	}
}

void	ft_single_color(char *addr)
{
	t_elem	*elem = NULL;

	for (int i = 0; addr[i]; i+=4)
	{
		elem_add(&elem, new_elem(*(int *)addr));
	}
}
