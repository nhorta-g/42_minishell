#include <minishell.h>

static int	is_value(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (1);
	return (0);
}

t_envplist	*fetch_node(char *str)
{
	t_envplist	*t;
	char		*name;

	t = envplist()->next;
	name = copy_name(str);
	while (t)
	{
		if (!ft_strcmp(name, t->var_name))
		{
			free(name);
			return (t);
		}
		t = t->next;
	}
	free(name);
	return (NULL);
}

void	export_print(void)
{
	t_envplist	*t;
	int			i;

	t = envplist()->next;
	i = 0;
	order_envplist();
	while (i < ft_envplstsize())
	{
		if (i == t->pos)
		{
			printf("declare -X %s", t->var_name);
			if (t->var_value)
				printf("=\"%s\"", t->var_value);
			printf("\n");
			i++;
			t = envplist()->next;
		}
		else
			t = t->next;
	}
}

void	cmd_export(t_cleanlist *node)
{
	int		i;

	i = 0;
	g_exit_status = 0;
	if (!node->av[1])
		export_print();
	while (node->av[++i])
	{
		if (!is_alpha(node->av[i][0]))
		{
			g_exit_status = 1;
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(node->av[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
		else
		{
			if (is_value(node->av[i]))
			{
				if (fetch_node(node->av[i]))
				{
					free(fetch_node(node->av[i])->var_value);
					free(fetch_node(node->av[i])->full);
					fetch_node(node->av[i])->var_value = \
					copy_value(node->av[i]);
					fetch_node(node->av[i])->full = ft_strcpy(node->av[i]);
				}
				else
					add_envpnode(new_envpnode(copy_name(node->av[i]), \
					copy_value(node->av[i]), ft_strcpy(node->av[i])), \
					envplist());
			}
			else
			{
				if (fetch_node(node->av[i]))
					return ;
				add_envpnode(new_envpnode(copy_name(node->av[i]), NULL, \
				ft_strcpy(node->av[i])), envplist());
			}
		}
	}
	update_envp();
}
