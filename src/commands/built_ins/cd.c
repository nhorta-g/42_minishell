#include <minishell.h>

static void	change_path()
{
	if (fetch_node("OLDPWD"))
		free(fetch_node("OLDPWD")->var_value);
	if (fetch_node("OLDPWD") && fetch_node("PWD"))
		fetch_node("OLDPWD")->var_value = fetch_node("PWD")->var_value;
	if (fetch_node("PWD"))
		fetch_node("PWD")->var_value = getcwd(NULL, 0);
}

void	cmd_cd(t_arglist *node)
{
	char	*s;
	char	*err_msg;

	g_exit_status = 0;
	if (node->ac > 2)
	{
		g_exit_status = 2;
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return ;
	}
	s = node->av[1];
	if (node->ac == 1 || !ft_strcmp(node->av[1], "~"))
		s = fetch_node("HOME")->var_value;
	if (chdir(s) == -1)
	{
		g_exit_status = 2;
		err_msg = ft_strjoin("minishell: cd: ", node->av[1]);
		perror(err_msg);
		free(err_msg);
		return ;
	}
	change_path();
}
