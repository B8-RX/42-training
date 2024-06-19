/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 06:14:16 by ssghioua          #+#    #+#             */
/*   Updated: 2023/11/27 06:28:30 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list -> content = content;
	list -> next = NULL;
	return (list);
}
/*
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current -> next;
		if (del)
			del(current -> content);
		free(current);
		current = next;
	}
		*lst = NULL;
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_content;
	
	new_list = NULL;
	if (!lst || !if || !del)
		return (new_list);
	while (lst)
	{
		if (f)
			new_content = f(ft_lstnew(lst -> content));
		else
			new_content = ft_lstnew(lst -> content);
		if (!new_content && del)
		{	
			ft_lstclear(&new_list, del);
		}
		else
			ft_lstadd_back(&new_list, new_content);
		lst = lst -> next;
	}
	return (new_list);
}*/
