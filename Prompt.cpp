#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Prompt.h"
#include "Search.h"
#include "Edit.h"


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
        printf("4. Borrar entrada por cedula\n");
        printf("5. Editar entrada por cedula\n");
        printf("Ponga cualquier pulse cualquier otra tecla para salir\n");
        char input = getch();
        int entries;
        char*** lData;
        FILE* test = fopen(file, "r");
        if (test != NULL)
        {
            entries = CountEntries(file);
            lData = LoadData(file);
        }

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
                for (int j = 0; j < 6; j++)
                    printf("%s ", lData[i][j]);
                fputc('\n', stdout);
            }
            break;
        }
        case '3':{
            char* buff = (char*)calloc(1024,1);
            int index;
            printf("Escriba la cedula que quiere buscar: ");
            if ((index = GetIndex(gets(buff), lData, entries)) == -1) 
                printf("La entrada no existe\n");
            else
            {
                printf("La entrada correspondiente es: ");
                for (int i = 0; i < 6; i++)
                    printf("%s ", lData[index][i]);
                putc('\n',stdout);
            }
            free(buff);
            break;
        }
        case '4':{
            char* buff = (char*)calloc(1024,1);
            int index;
            printf("Escriba la cedula de la linea por borrar: ");
            if ((index = GetIndex(gets(buff), lData, entries)) == -1) 
                printf("La entrada no existe\n");
            else
            {
                DeleteLine(lData, &entries, index);
                OverwriteData(file, lData, entries);
            }
            free(buff);
            break;
        }
        case '5':{
            char* buff = (char*)calloc(1024,1);
            int index;
            printf("Escriba la cedula de la linea por editar: ");
            if ((index = GetIndex(gets(buff), lData, entries)) == -1) 
                printf("La entrada no existe\n");
            else
            {
                EditLine(lData, index);
                OverwriteData(file, lData, entries);
            }
            free(buff);
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
        lData[i] = (char**)malloc(sizeof(char*) * 6);
        for (int j = 0; j < 6; j++)
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
    CharByChar(buff, "i11", '\0');
    if (buff[0] == '*')
    {
        printf_s("Error: '*' como primer caracter no es valido",stderr);
        return (char*)"ERROR";
    }
    strncat(buff, ",", 128);
    strncat(line, buff, 128);

    //Nombre
    printf("Ponga su o sus nombres: ");
    CharByChar(buff, "n",'\0');
    strncat(buff, ",", 128);
    strncat(line, buff, 128);

    //Apellidos
    printf("Ponga sus apellidos: ");
    CharByChar(buff, "n",'\0');
    strncat(buff, ",", 128);
    strncat(line, buff, 128);

    //Edad
    printf("Ponga su edad: ");
    CharByChar(buff, "i3",'\0');
    strncat(buff, ",", 128);
    strncat(line, buff, 128);

    printf("Ponga sus ahorros: ");
    CharByChar(buff, "f2",'\0');
    strncat(buff, ",", 128);
    strncat(line, buff, 128);

    printf("Ponga su contrasena: ");
    CharByChar(buff, "n",'x');
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
        fputs("*Cedula,Nombre,Apellido,Edad,Ahorros,Password,\n", data);    
    fputs(line, data);
    fclose(data);
}

void OverwriteData(char* file, char***lData, int entries)
{
    FILE* data = fopen(file, "w");
    fputs("*Cedula,Nombre,Apellido,Edad,Ahorros,Password,\n", data);

    for (int i = 0; i < entries; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            fputs(lData[i][j], data);
            fputc(',', data);
        }
        fputc('\n', data);
    }

    fclose(data);
}

void CharByChar(char* buff, char* conditions, char dispChar) //Set display char to \0 to show user input, Conditions: i3 = age i11 = cedula f2 = ahorros n = nombre (no espacios)
{
    char input;
    memset(buff, '\0', 128);

    int i = 0;
    int afterDot = 0;
    char wasDotPlaced = 0;
    while (input = getch())
    {
        if (input == '\b' && i > 0)
        {
            if (buff[i - 1] == '.')
            {
                wasDotPlaced = 0;
                afterDot = 0;
            }
            buff[i - 1] = '\0';
            i--;
            printf("\b \b");
            if (wasDotPlaced)
                afterDot--;
        }
        if (input == 13)
            break;
        else
        {
            if (strcmp(conditions, "i3") == 0)
            {
                if (isdigit(input) && i < 3)
                {
                    buff[i] = input;
                    i++;
                    (dispChar == '\0') ? putc(input, stdout) : putc(dispChar, stdout);
                }
                
            }
            if (strcmp(conditions, "i11") == 0)
            {
                if (isdigit(input) && i < 11)
                {
                    buff[i] = input;
                    i++;
                    (dispChar == '\0') ? putc(input, stdout) : putc(dispChar, stdout);
                }
                
            }
            
            if (strcmp(conditions, "f2") == 0)
            {   
                if (input == '.' && !wasDotPlaced)
                {
                    buff[i] = input;
                    i++;
                    wasDotPlaced = 1;
                    (dispChar == '\0') ? putc(input, stdout) : putc(dispChar, stdout);
                }
                if (isdigit(input) && afterDot < 2)
                {
                    buff[i] = input;
                    i++;
                    (dispChar == '\0') ? putc(input, stdout) : putc(dispChar, stdout);
                    if (wasDotPlaced)
                    {
                        afterDot++;
                    }
                }
            }
            if (strcmp(conditions, "n") == 0)
            {
                if (isalpha(input))
                {
                    buff[i] = input;
                    i++;
                    (dispChar == '\0') ? putc(input, stdout) : putc(dispChar, stdout);
                }
            }
        }
    }
    putc('\n', stdout);
}