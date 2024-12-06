/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:22:31 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/10/06 15:59:24 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
	{
		return (NULL);
	}
	new_node->next = NULL;
	new_node->content = content;
	return (new_node);
}
/*
int main()
{
	int content1 = 1;
	int content2 = 2;
	int content3 = 3;
	int *ptr1 = &content1;
	int *ptr2 = &content2;
	int *ptr3 = &content3;
	t_list	*node1;
	t_list	*node2;
	t_list	*node3;
	node1 = ft_lstnew(ptr1);
	node2 = ft_lstnew(ptr2);
	node3 = ft_lstnew(ptr3);
	node1->next = node2;
	node2->next = node3;
	//iteration sur la list
	t_list	*current = node1;
	while (current != NULL)
	{
		printf("%d\n", *((int *)(current->content)));
		current = current->next;
	}
	return (0);
}
*/
