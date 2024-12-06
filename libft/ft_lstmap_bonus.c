/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 20:05:08 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/10/18 20:39:22 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*old_content;

	if (lst == NULL || del == NULL || f == NULL)
		return (NULL);
	new_list = NULL;
	while (lst != NULL)
	{
		old_content = (*f)(lst->content);
		new_node = ft_lstnew(old_content);
		if (new_node == NULL)
		{
			del(old_content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
/*
void fun(void *ptr)
{
	free(ptr);
}

void *f(void *ptr)
{
	int new_data = *(int *)ptr * 10;
	void *new_data_ptr = &new_data;
	return (new_data_ptr);
}

#include <stdio.h>
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
	t_list	*clone = ft_lstmap(node1, &f, &fun);
	//iteration sur les list
        t_list  *current = clone;
	printf("Cloned list :\n");
        while (current != NULL)
        {
                printf("%d\n", *((int *)(current->content)));
                current = current->next;
        }
}
*/
