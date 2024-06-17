/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c			                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 01:24:40 by ssghioua          #+#    #+#             */
/*   Updated: 2024/06/18 01:24:42 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/push_swap.h"

void move_to_stack_a(t_stack **stack_a, t_stack **stack_b) {
    t_stack *best_move_node;

    best_move_node = get_best_move_node(*stack_b);

    while (*stack_b != best_move_node) {
        if (best_move_node->in_upper_half)
            rb(stack_b, 1);
        else
            rrb(stack_b, 1);
    }

    while (*stack_a != best_move_node->target) {
        if (best_move_node->target->in_upper_half)
            ra(stack_a, 1);
        else
            rra(stack_a, 1);
    }

    pa(stack_a, stack_b, 1);
}

void move_to_stack_b(t_stack **stack_a, t_stack **stack_b) {
    t_stack *best_move_node;

    best_move_node = get_best_move_node(*stack_a);

    while (*stack_a != best_move_node) {
        if (best_move_node->in_upper_half)
            ra(stack_a, 1);
        else
            rra(stack_a, 1);
    }

    while (*stack_b != best_move_node->target) {
        if (best_move_node->target->in_upper_half)
            rb(stack_b, 1);
        else
            rrb(stack_b, 1);
    }

    pb(stack_a, stack_b, 1);
}
