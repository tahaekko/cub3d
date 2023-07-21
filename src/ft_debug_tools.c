#include "cub3d.h"

static int	ft_elem_exist(t_elem *list, int elem)
{
	while (list)
	{
		if (list->content == elem)
			return (1);
		list = list->next;
	}
	return (0);
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
	t_elem	*head = *node;
	// printf("%p\n", *node);
	// printf("%p\n", *node);
	if (!*node)
		*node = back;
	else
	{
		while ((*node)->next)
			*node = (*node)->next;
		(*node)->next = back;
		*node = head;
	}
}

t_elem	*ft_single_color(int *addr)
{
	t_elem	*elem = NULL;

	for (int i = 0; addr[i]; i++)
	{
		// printf("int %x\n", addr[i]);
		if ((!elem || !ft_elem_exist(elem, addr[i])))
			elem_add(&elem, new_elem(addr[i]));
	}
	return (elem);
}
