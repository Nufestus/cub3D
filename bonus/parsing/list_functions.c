/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:36:53 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/09 15:21:33 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	ft_lstsize(t_map *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_map	*ft_lstlast(t_map *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_map **lst, t_map *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
}

t_map	*ft_lstnew(char *content)
{
	t_map	*newnode;

	newnode = (t_map *)malloc(sizeof(t_map));
	if (!newnode)
		return (NULL);
	newnode->line = content;
	newnode->next = NULL;
	return (newnode);
}

void	newnode(char *str, t_map **head)
{
	t_map	*newnode;

	newnode = ft_lstnew(ft_strdup(str));
	ft_lstadd_back(head, newnode);
}
