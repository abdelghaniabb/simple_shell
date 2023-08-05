#include "main.h"
#include <limits.h>


/**
  * cd_builtin - Change the current directory of the process.
  * @tokens: Command tokens (including the "cd" command and optional directory).
  * Return: Always returns 0 to indicate success.
  */
int cd_builtin(char **tokens)
{
    char *new_dir;
    char cwd[PATH_MAX];

    if (tokens[1] == NULL || _strcmp(tokens[1], "~") == 0)
    {
        new_dir = _getenv("HOME");
    }
    else if (_strcmp(tokens[1], "-") == 0)
    {
        char *prev_dir = _getenv("OLDPWD");
        if (prev_dir == NULL)
        {
            fprintf(stderr, "./hsh: 1: cd: can't cd to %s\n", tokens[1]);
            return 0;
        }
        new_dir = prev_dir;
    }
    else
    {
        new_dir = tokens[1];
    }

    
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        if (chdir(new_dir) == -1)
        {
            fprintf(stderr, "./hsh: 1: cd: can't cd to %s\n", tokens[1]);
        }
        else
        {
            setenv("OLDPWD", cwd, 1);
            if (getcwd(cwd, sizeof(cwd)) != NULL)
            {
                setenv("PWD", cwd, 1);
            }
        }
    }
    else
    {
        fprintf(stderr, "./hsh: 1: cd: can't get current directory\n");
    }

    return 0;
}
