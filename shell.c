#include "main.h"

void p_error(char *av, char *number)
{
	write(STDERR_FILENO, av, _strlen(av));
	write(STDERR_FILENO, ": 1: exit: Illegal number: ", _strlen(": 1: exit: Illegal number: "));
	write(STDERR_FILENO, number, _strlen(number));
	write(STDERR_FILENO, "\n", 1);
}

int main(int __attribute__((unused)) argc, char *av[])
{
    char *buffer = NULL, *path_env, *path, **tokens;
    size_t buf_s = 0;
    int flag = 0, len = 0, exit_status = 0;

    while (1)
    {
        if (isatty(0))
            write(STDOUT_FILENO, "#meisfun$ ", 9);

        len = getline(&buffer, &buf_s, stdin);

        if (len == -1)
            free(buffer), exit(0);

        if (len == EOF)
            _EOF(buffer);

        if (*buffer == '\n')
        {
            free(buffer);
            continue;
        }

        buffer[len - 1] = '\0';

        if (is_whitespace(buffer) == 1)
            continue;

        tokens = make_tokens(buffer);

        if (_strcmp(tokens[0], "exit") == 0)
        {
            /* Handle the exit command with an optional status argument */
            if (tokens[1] != NULL)
            {
                /* Convert the status argument to an integer */
                exit_status = atoi(tokens[1]);
                if (exit_status == 0 && tokens[1][0] != '0')
                {
                    /* If atoi fails to convert the argument, print an error and continue */
                    p_error(av[0], tokens[1]);
                    free(buffer);
                    buffer = NULL;
                    buf_s = 0;
                    free(tokens);
                    continue;
                }
            }
            /* Free resources and exit with the specified status */
            free(buffer);
            free(tokens);
            exit(exit_status);
        }
        else if (_strcmp(tokens[0], "setenv") == 0)
        {
            /* Handle the setenv command */
            if (tokens[1] != NULL && tokens[2] != NULL)
            {
                /* Call setenv with the specified variable and value */
                if (setenv(tokens[1], tokens[2], 1) != 0)
                {
                    /* If setenv fails, print an error and continue */
                    p_error(av[0], "Failed to set environment variable");
                }
            }
            else
            {
                /* Print an error if the syntax is incorrect and continue */
                p_error(av[0], "Invalid syntax for setenv command");
            }
        }
        else if (_strcmp(tokens[0], "unsetenv") == 0)
        {
            /* Handle the unsetenv command */
            if (tokens[1] != NULL)
            {
                /* Call unsetenv with the specified variable */
                if (unsetenv(tokens[1]) != 0)
                {
                    /* If unsetenv fails, print an error and continue */
                    p_error(av[0], "Failed to unset environment variable");
                }
            }
            else
            {
                /* Print an error if the syntax is incorrect and continue */
                p_error(av[0], "Invalid syntax for unsetenv command");
            }
        }
        else if (_strcmp(tokens[0], "env") == 0)
        {
            free(tokens);
            print_env();
            continue;
        }
        else
        {
            path_env = _getenv("PATH");
            path = search_command(tokens[0], path, path_env);

            if (path == NULL)
                path = tokens[0];
            else
                flag = 1;

            execute_cmd(tokens, av[0], path);
            free(buffer);
            buffer = NULL;
            buf_s = 0;
            free(tokens);

            if (flag == 1)
                free(path);
        }
    }

    return (0);
}

