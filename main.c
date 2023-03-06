/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:40:51 by aarsenio          #+#    #+#             */
/*   Updated: 2023/03/04 00:02:07 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main()
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		tokenizer(input);
		print_toklist();
		destroy_list(list());
		free(input);
	}
}
