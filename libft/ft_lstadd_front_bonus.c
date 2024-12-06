/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:00:04 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/10/06 16:22:45 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (lst == NULL || new == NULL)
		return ;
	else if (*lst == NULL)
		*lst = new;
	else
	{
		temp = *lst;
		*lst = new;
		new->next = temp;
	}
}
/*
int main()
{
        int content1 = 1;
        int content2 = 2;
        int content3 = 3;
	int content4 = 999;
        int *ptr1 = &content1;
        int *ptr2 = &content2;
        int *ptr3 = &content3;
	int *ptr4 = &content4;
        t_list  *node1;
        t_list  *node2;
        t_list  *node3;
	t_list	*node4;
        node1 = ft_lstnew(ptr1);
        node2 = ft_lstnew(ptr2);
        node3 = ft_lstnew(ptr3);
	node4 = ft_lstnew(ptr4);
        node1->next = node2;
        node2->next = node3;
	ft_lstadd_front(&node1, node4);
        iteration sur la list
        t_list  *current = node1;
        while (current != NULL)
        {
                printf("%d\n", *((int *)(current->content)));
                current = current->next;
        }
        return (0);
}
*/
