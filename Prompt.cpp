#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#include "Prompt.h"
#include "Search.h"

int main(int argc, char **argv)
{
    int returnN = 0;
    //Check if argument was passed
    if (argc < 2)
    {
        printf_s("Error: no filename argument was passed\n", stderr);
        return 100;
    }
    
    returnN = ProgramLoop(argv[1]);

    return returnN;
}

int ProgramLoop(char* file)
{
    strcat(file, ".txt");
    int quitflag = 0;
    while (!quitflag)
    {
        printf("Que quiere hacer?\n");
        printf("1. Registrar datos\n");
        printf("2. Listar todos los datos\n");
        printf("3. Buscar entrada por cedula\n");
        printf("Ponga cualquier pulse cualquier otra tecla para salir\n");
        char input = getch();
        int entries = CountEntries(file);
        char*** lData = LoadData(file);

        switch (input)
        {
        case '1':{
            char* line = PromptUser();
            if (strcmp(line, "ERROR") == 0)
                quitflag = 1;
            else
                AppendData(line, file);
            break;
        }
        case '2':{
            for (int i = 0; i < entries; i++)
            {
                for (int j = 0; j < 4; j++)
                    printf("%s ", lData[i][j]);
                fputc('\n', stdout);
            }
            
            break;
        }
        default:
            return 0;
            break;
        }
    }
    return 0;
}

char*** LoadData(char* file)
{
    int entries = CountEntries(file); //Starts at 0 because we know first line is a header
    
    FILE* dataFile = fopen(file, "r");
    if (dataFile == NULL)
    {
        printf_s("El archivo %s no existe\n",stderr);
        return (char***)0;
    }
    
    char tmp;
    char* buff = (char*)calloc(1024,1);

    char*** lData = (char***)malloc(sizeof(char**) * entries);
    for (int i = 0; i < entries; i++)
    {
        lData[i] = (char**)malloc(sizeof(char*) * 4);
        for (int j = 0; j < 4; j++)
            lData[i][j] = (char*)calloc(1024, 1); //Initialize all lines
    }

    auto ClearBuff = [&] (int len) { //lambda function for resetting buffer to 0;
        for (int i = 0; i < len; i++)
            buff[i] = '\0';
    };

    while (fgetc(dataFile) != '\n') //skip header
        0;
    
    //Here data is loaded into the entry list
    int i = 0; int tEntry = 0; int tLine = 0;
    while ((tmp = fgetc(dataFile)) != EOF)
    {
        switch (tmp)
        {
        case '\n':
            tEntry = 0;
            tLine++;
            break;
        case ',':
            strcpy(lData[tLine][tEntry], buff);
            printf("%d ",tEntry);
            ClearBuff(1024);
            i = 0;
            tEntry++;
            break;
        default:
            buff[i] = tmp;
            i++;
            break;
        }
    }
    fclose(dataFile);
    free(buff);
    return lData;
}

int CountEntries(char* file)
{
    FILE* dataFile = fopen(file, "r");
    if (dataFile == NULL)
    {
        printf_s("El archivo %s no existe\n",stderr);
        return -1;
    }

    char tmp;
    int entries = 0;
    
    while ((tmp = fgetc(dataFile)) != EOF)
    {
        if (tmp == '\n')
            entries++;
    }
    fclose(dataFile);
    return entries - 1; //Para ignorar el header
}

char* PromptUser()
{
    char* buff = (char*)calloc(128,1);
    char* line = (char*)calloc(1024,1);

    //Cedula
    printf("Ponga su numero de cedula: ");
    gets(buff);
    if (buff[0] == '*')
    {
        printf_s("Error: '*' como primer caracter no es valido",stderr);
        return (char*)"ERROR";
    }
    
    strncat(buff, ",", 128);
    strncat(line, buff, 128);

    //Nombre
    printf("Ponga su o sus nombres: ");
    gets(buff);
    strncat(buff, ",", 128);
    strncat(line, buff, 128);

    //Apellidos
    printf("Ponga sus apellidos: ");
    gets(buff);
    strncat(buff, ",", 128);
    strncat(line, buff, 128);

    //Edad
    printf("Ponga su edad: ");
    gets(buff);
    strncat(buff, ",\n", 128);
    strncat(line, buff, 128);

    free(buff);
    return line;
}

void AppendData(char* line, char* filename)
{
    int isFilePresent = 1;
    
    //Check if file exists
    if (fopen(filename, "r") == NULL)
        isFilePresent = 0;

    FILE* data = fopen(filename, "a+");
    if (!isFilePresent)
        fputs("*Cedula,Nombre,Apellido,Edad,\n", data);    
    fputs(line, data);
}