/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:06:29 by ssghioua          #+#    #+#             */
/*   Updated: 2024/01/16 11:06:31 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define BASE_LOW "0123456789abcdef"
# define BASE_UP "0123456789ABCDEF"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include "../../../libft/src/include/libft.h"

typedef struct s_flags {
	int		period;
	int		precision;
	int		blank;
	int		zero;
	int		sharp;
	int		plus;
	int		minus;
	int		width;
}	t_flags;

typedef struct s_printf {
	va_list	args;
	t_flags	*flags;
	char	specifier;
	int		flags_len;
	int		format_len;
	int		updated;
	char	*base;
	int		negative_nbr;
	int		error_format;
}	t_printf;

int			ft_printf(const char *format, ...);
t_printf	*ft_init_printf_props(t_printf *props);
int			ft_end_process(t_printf *printf_props, const char *format);
int			ft_verify_format(t_printf *printf_props, const char *format);
t_printf	*ft_verify_flags(t_printf *printf_props, const char *format, int i);
t_printf	*ft_format_processing(t_printf **printf_props, const char *format);
char		*ft_flags_processing(t_printf *printf_props, char *str);
t_printf	*ft_handle_flags(t_printf *printf_props, const char *format);
int			ft_handle_minus_flag(t_printf *printf_props, char prev_char);
int			ft_handle_plus_flag(t_printf *printf_props, char prev_char);
int			ft_handle_period_flag(t_printf *printf_props);
int			ft_handle_zero_flag(t_printf *printf_props,
				const char *format, int i);
int			ft_handle_num_flag(t_printf *printf_props,
				const char *format, int i);
int			ft_handle_sharp_flag(t_printf *printf_props,
				const char *format, int i);
void		*ft_handle_err_format(t_printf *printf_props,
				const char *format, int i);
void		ft_save_specifier_if_found(t_printf *printf_props,
				const char format);
void		ft_handle_s_specifier(t_printf *printf_props);
char		*ft_itoa_printf(t_printf *printf_props, int nb);
char		*ft_uitoa(unsigned int n);
char		*ft_ultoa(t_printf *printf_props, unsigned long n);
int			ft_atoi_free(char *str);
int			ft_print_char(t_printf *printf_props, char c);
int			ft_handle_char_with_flags(t_printf *printf_props, char c);
void		*ft_print_percent_sign(t_printf *printf_props);
int			ft_print_str(t_printf *printf_props, char *str);
char		*ft_update_str(t_printf *printf_props, char *str);
char		*ft_slice_str(t_printf *printf_props, char *str);
char		*ft_set_infill(t_printf *props, char *str);
char		*ft_populate_infill(t_printf *printf_props,
				char *infill, char *str);
char		*ft_infill_precision(t_printf *props, char *str_input);
char		*ft_infill_width(t_printf *props, char *infill, int input_len);
char		*ft_justify_infill(t_printf *props, char *infill, char *str);
char		*ft_justify_infill_left(t_printf *printf_props,
				char *str, char *infill);
char		*ft_justify_infill_right(t_printf *printf_props,
				char *str, char *infill);
char		*ft_append_parity(t_printf *printf_props, char *str);
char		*ft_append_blank(t_printf *printf_props, char *src);
char		*ft_append_prefix_hexa(t_printf *printf_props, char *str);
char		*ft_append_char_to_str(char *str, char c, int c_position);
char		*ft_fill_zero(int size);
// char		*ft_strjoin(char *s1, char *s2);
char		*ft_substr(const char *s, unsigned int start, size_t len);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *str);

#endif // !FT_PRINTF_H
