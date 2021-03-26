#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "search.h"

int GetIndex(char* cedula, char*** lData, int entries)
{
    for (int i = 0; i < entries; i++)
    {
        if (strcmp(lData[i][0], cedula) == 0)
            return i;
    }
    return -1;
}