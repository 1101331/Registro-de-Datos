#include <stdio.h>
#include <stdlib.h>
#include "Prompt.h"
#include "Edit.h"
#include "Search.h"

void DeleteLine(char*** lData, int* entries, int index)
{
    for (int i = index; i < *entries - 1; i++)
    {
        for (int j = 0; j < 6; j++)
            lData[i][j] = lData[i + 1][j];
    }
    *entries = *entries - 1;
}

void EditLine(char*** lData, int index)
{
    for (int i = 1; i < 6; i++)
    {
        for (int j = 0; j < 1024; j++)
            lData[index][i][j] = '\0';
    }

    //Nombre
    printf("Ponga su o sus nombres: ");
    CharByChar(lData[index][1], "n", '\0');

    //Apellidos
    printf("Ponga sus apellidos: ");
    CharByChar(lData[index][2], "n", '\0');

    //Edad
    printf("Ponga su edad: ");
    CharByChar(lData[index][3], "i3", '\0');

    printf("Ponga sus ahorros: ");
    CharByChar(lData[index][4], "f2", '\0');

    printf("Ponga su contrasena: ");
    CharByChar(lData[index][5], "n", 'x');
}