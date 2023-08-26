#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

//https://gist.github.com/kylieCat/86744517063e8ec2daf8c69363720ecd

///1/2 indque a readline de ne pas compter les char dans la taille du prompt evite bug d'affichage
# define ORANGE "\1\033[38;5;208m\2"
# define RESET "\1\x1b[0m\2"
# define RED "\1\033[38;5;12m\2"

typedef struct s_list
{
	char *s;
	struct s_list *next;
}t_list;

void	lst_clear(t_list **lst)
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->s);
		free(*lst);
		*lst = tmp;
	}
}

void	add_to_list(char *s, t_list **list)
{
	t_list *new;
	t_list	*lst;

	new = malloc(sizeof(t_list));
	if (!new)
	{
		free(s);
		lst_clear(list);
		return ;
	}
	new->next = NULL;
	new->s = s;
	if (!*list)
	{
		*list = new;
		return ;
	}
	lst = *list;
	while (lst->next)
		lst = lst->next;
	lst->next = new;
}

long ft_strlen(char *s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

void    ft_strcpy(char *dest, char *src)
{
    int i;

    i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
	dest[i] = 0;
}

void	print_history(t_list *list)
{
	int		i;

	i = 1;
	while (list)
	{
		printf("    %d  %s\n", i, list->s);
		i++;
		list = list->next;
	}
}

int main(int argc, char *argv[])
{
    char    *buffer;
    char    prompt[100];
    int     tty;
	t_list	*history;

	history = NULL;
    tty = isatty(0);
    if (tty)
    {
        ft_strcpy(prompt, RED);
        ft_strcpy(prompt + ft_strlen(prompt), "minisheljoharymadaguen> ");
        ft_strcpy(prompt + ft_strlen(prompt), RESET);
    }
    else
        prompt[0] = 0;
 
    while(1)
    {
        buffer = readline(prompt);
        if (!buffer)
            break;
		//rl_replace_line("test", 0);
		// minishell(buffer);
		add_history(buffer);
		add_to_list(buffer, &history);
		if (strcmp("history", buffer) == 0)//option n pas mal? le x deniers? passer lst size et decrementer la taille jusau'a au'elle vaille n
			print_history(history);
		if (!history)
			break ;
    }
	lst_clear(&history);
	rl_clear_history();
    if (tty)
        printf("exit\n");
    return 0;
}

