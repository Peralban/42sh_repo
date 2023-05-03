/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** main.c
*/

#include "mysh.h"
#include "my.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static char *my_getline(int *error)
{
    size_t size = 0;
    char *line = NULL;

    if (getline(&line, &size, stdin) == -1) {
        my_exit((char *[2]){"Error", NULL}, error);
        return NULL;
    }
    line[strlen(line) - 1] = '\0';
    return line;
}

int main(int ac, char **av, char **env)
{
    char *line = NULL;
    int error = 0;
    char **cmd = NULL;
    char **env_cpy = my_arraydup(env);

    if (var_are_init(env_cpy) == false)
        setup_env(env_cpy);
    while (error != -1) {
        print_prompt(env_cpy, error);
        error = 0;
        line = my_getline(&error);
        if (line == NULL)
            continue;
        line = detect_variables(line, env, &error);
        //printf("line modified: %s\n", line);
        cmd = my_str_to_word_array(line, " \t");
        //for (int i = 0; cmd[i] != NULL; i++)
            //printf("cmd[%d] %s\n", i, cmd[i]);
        error = built_in(cmd, env_cpy, &error);
        if (error != 2)
            continue;
    }
    return 0;
}
