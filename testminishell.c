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

int main(int argc, char *argv[])
{
    char    *buffer;
    char    prompt[100];
    int     tty;

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
		printf("You entered: %s\n", buffer);
		//rl_replace_line("test", 0);
		// minishell(buffer);
		add_history(buffer);
		free(buffer);
    }
	rl_clear_history();
    if (tty)
        printf("exit\n");
    return 0;
}

