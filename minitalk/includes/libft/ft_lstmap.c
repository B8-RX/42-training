/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:37:23 by ssghioua          #+#    #+#             */
/*   Updated: 2023/11/29 10:37:40 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_content;

	new_list = NULL;
	if (!lst)
		return (new_list);
	while (lst)
	{
		if (f)
			new_content = ft_lstnew(f(lst -> content));
		else
			new_content = ft_lstnew(lst -> content);
		if (!new_content)
		{	
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		else
			ft_lstadd_back(&new_list, new_content);
		lst = lst -> next;
	}
	return (new_list);
}
