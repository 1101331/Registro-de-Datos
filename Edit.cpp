#include <stdio.h>
#include <stdlib.h>
#include "Edit.h"
#include "Search.h"

void DeleteLine(char*** lData, int* entries, int index)
{
    for (int i = index; i < *entries - 1; i++)
    {
        for (int j = 0; j < 4; j++)
            lData[i][j] = lData[i + 1][j];
    }
    *entries = *entries - 1;
}

void EditLine(char*** lData, int index)
{
    for (int i = 1; i < 4; i++)
    {
        for (int j = 0; j < 1024; j++)
            lData[index][i][j] = '\0';
    }

    //Nombre
    printf("Ponga su o sus nombres: ");
    gets(lData[index][1]);

    //Apellidos
    printf("Ponga sus apellidos: ");
    gets(lData[index][2]);

    //Edad
    printf("Ponga su edad: ");
    gets(lData[index][3]);
}