#include "minishell.h"

void	ft_echo_change(char *str, t_list *env)
{
	int		start;
	int		end;

	start = 0;
	end = 0;

	if (ft_strchr(str, '\\'))
	{
		while (str[start] && str[start] != '$')
			start++;
		end = start;
		while (str[end] && str[end] != '\\')
			end++;
		if(ft_echo_change2(str, start, end) == 0)
			ft_echo_change3(str, env);
	}
	else
	{
		start = 0;
		while (*str != '$' && *str != '\0')
		{
			printf("%c", *str);
			str++;
		}
		start = ft_check_echo(ft_strchr(str, '$'), env);
	}
}

int	ft_echo_change2(char *str, int start, int end)
{
	if (str[end] == '\0' || start == end - 1)
	{
		start = 0;
		while (str[start] != '\0')
		{
			if (str[start] == '\\')
				start++;
			if (str[start] != '\0')
				printf ("%c", str[start]);
			start++;
		}
		return (1);
	}
	else if (start < end - 1)
	{
		start = 0;
		while (str[start] != '$')
		{
			printf("%c", str[start]);
			start++;
		}
		printf("%s", ft_strchr(str, '\\') + 1);
		return (1);
	}
	return (0);
}

void	ft_echo_change3(char *str, t_list *env)
{
	int	start;

	start = 0;
	while (str[start] != '\\')
	{
		printf("%c", str[start]);
		start++;
	}
	start = ft_check_echo(str, env);
}