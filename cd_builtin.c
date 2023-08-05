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

    if (tokens[1] == NULL || _strcmp(tokens[1], "~") == 0)
    {
        new_dir = _getenv("HOME");
    }
    else if (_strcmp(tokens[1], "-") == 0)
    {
        new_dir = _getenv("OLDPWD");
    }
    else
    {
        new_dir = tokens[1];
    }

    if (chdir(new_dir) == -1)
    {
        p_error(tokens[0], "Failed to change directory");
    }
    else
    {
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            setenv("PWD", cwd, 1);
        }
    }

    return 0;
}
