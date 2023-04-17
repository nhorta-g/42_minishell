#include <minishell.h>

int	builtins(t_cleanlist *node)
{
	if(!node->av[0])
		return (0);
	if (!ft_strcmp(node->av[0], "echo"))
		cmd_echo(node);
	else if (!ft_strcmp(node->av[0], "cd"))
		cmd_cd(node);
	else if (!ft_strcmp(node->av[0], "pwd"))
		cmd_pwd();
	else if (!ft_strcmp(node->av[0], "export"))
		cmd_export(node);
	else if (!ft_strcmp(node->av[0], "unset"))
		cmd_unset(node);
	else if (!ft_strcmp(node->av[0], "env"))
		cmd_env();
	else if (!ft_strcmp(node->av[0], "exit"))
		cmd_exit();
	else
		return (0);
	return (1);
}
