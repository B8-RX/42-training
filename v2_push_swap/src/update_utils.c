/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 01:20:52 by ssghioua          #+#    #+#             */
/*   Updated: 2024/06/18 01:20:54 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/push_swap.h"

void update_nodes_a(t_stack *stack_a, t_stack *stack_b) {
    update_index(stack_a);
    update_index(stack_b);
    find_target_position_a(stack_a, stack_b);
    count_move_steps_a(stack_a, stack_b);
    set_best_move(stack_a);
}

void update_nodes_b(t_stack *stack_a, t_stack *stack_b) {
    update_index(stack_a);
    update_index(stack_b);
    find_target_position_b(stack_a, stack_b);
	count_move_steps_b(stack_a, stack_b);
    set_best_move(stack_b);

}

void update_index(t_stack *stack) {
    size_t i;
    size_t len;

    i = 0;
    len = get_stack_len(stack);
    if (!stack)
        return;
    while (stack) {
        stack->index = i;
        stack->in_upper_half = (i < len / 2);
        stack = stack->next;
        i++;
    }
}
