/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 05:16:24 by ssghioua          #+#    #+#             */
/*   Updated: 2024/08/24 05:16:25 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display_error_ext(char *ext, char *file)
{
	ft_putendl_fd_nl("ERROR EXTENSION: SUPPORT [.xpm] GET [.", 2);
	ft_putendl_fd_nl(ext, 2);
	ft_putendl_fd("]", 2);
	ft_putendl_fd(file, 2);
}
