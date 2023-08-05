#include "main.h"
/**
  * execute_cmd - exeuc
  * @tokens: token
  * @av: value
  * @path: the path
  * Return: 0 - 1
  */
int execute_cmd(char **tokens, char *av, char *path)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
	{
		perror(av);
		exit(1);
	}
	else if (pid == 0)
	{
		if (execve(path, tokens, environ) == -1)
		{
			perror(av);
			exit(2);
		}
	}
	else
		wait(&status);
	return (WEXITSTATUS(status));
}

void execute_commands(char *commands, char *av[])
{
    char *command, *saveptr;
    command = strtok_r(commands, ";", &saveptr);

    while (command != NULL)
    {
        /* Handle each command here, tokenize it and execute it as before */
        char **tokens = make_tokens(command);

        if (_strcmp(tokens[0], "exit") == 0)
        {
            /* Handle the exit command with an optional status argument */
            if (tokens[1] != NULL)
            {
                /* Convert the status argument to an integer */
                int exit_status = atoi(tokens[1]);
                if (exit_status == 0 && tokens[1][0] != '0')
                {
                    /* If atoi fails to convert the argument, print an error and continue */
                    p_error(av[0], tokens[1]);
                    free(tokens);
                    continue;
                }

                /* Free resources and exit with the specified status */
                free(tokens);
                exit(exit_status);
            }
            else
            {
                /* No status argument provided, simply exit */
                free(tokens);
                exit(0);
            }
        }
        else if (_strcmp(tokens[0], "cd") == 0)
        {
            /* Handle the cd command */
            cd_builtin(tokens);
            free(tokens);
        }
        else if (_strcmp(tokens[0], "env") == 0)
        {
            free(tokens);
            print_env();
        }
        else
        {
            /* Execute external commands */
            char *path_env = _getenv("PATH");
            char *path = search_command(tokens[0], NULL, path_env); /* Adjust the second argument based on your search_command implementation*/
            int flag = 0;

            if (path == NULL)
                path = tokens[0];
            else
                flag = 1;

            /* Execute the command */
            /* st = */ execute_cmd(tokens, av[0], path);

            free(tokens);
            if (flag == 1)
                free(path);
        }

        command = strtok_r(NULL, ";", &saveptr);
    }
}
