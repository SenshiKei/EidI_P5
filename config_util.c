//
// Created by belah on 30.12.2022.
//
#include <stdlib.h>
#include <stdio.h>

#include "config_util.h"

void exit_with_output(char* error)
{
    fprintf(stderr, "Error: %s\n", error);
    exit(EXIT_FAILURE);
}