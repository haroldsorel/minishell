/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:38:38 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/10/06 17:14:24 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	current = lst;
	if (current == NULL)
		return (NULL);
	while (current->next != NULL)
	{
		current = current->next;
	}
	return (current);
}
/*
int main()
{
        int content1 = 1;
        int content2 = 2;
        int content3 = 3;
        int content4 = 4;
        int content5 = 5;
        int content6 = 6;
        int content7 = 7;
        int content8 = 8;
        int *ptr1 = &content1;
        int *ptr2 = &content2;
        int *ptr3 = &content3;
        int *ptr4 = &content4;
        int *ptr5 = &content5;
        int *ptr6 = &content6;
        int *ptr7 = &content7;
        int *ptr8 = &content8;
        t_list  *node1;
        t_list  *node2;
        t_list  *node3;
        t_list  *node4;
        t_list  *node5;
        t_list  *node6;
        t_list  *node7;
        t_list  *node8;
        node1 = ft_lstnew(ptr1);
        node2 = ft_lstnew(ptr2);
        node3 = ft_lstnew(ptr3);
        node4 = ft_lstnew(ptr4);
        node5 = ft_lstnew(ptr5);
        node6 = ft_lstnew(ptr6);
        node7 = ft_lstnew(ptr7);
        node8 = ft_lstnew(ptr8);
        node1->next = node2;
        node2->next = node3;
        node3->next = node4;
        node4->next = node5;
        node5->next = node6;
        node6->next = node7;
        node7->next = node8;
        //iteration sur la list
	t_list  *current = node1;
        while (current != NULL)
        {
                printf("%d\n", *((int *)(current->content)));
                current = current->next;
        }
	printf("Content of the last node: %d", *((int *)((ft_lstlast(NULL))->content)));
	return (0);
}
*/
