#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* PromptUser();
void AppendData(char* line, char* filename);

int main(int argc, char **argv)
{
    //Check if argument was passed
    if (argc < 2)
    {
        printf_s("Error: no filename argument was passed\n", stderr);
        return 100;
    }
    
    char* line = PromptUser();
    if (strcmp(line, "ERROR") == 0)
    {
        return 100;
    }
    else
    {
        AppendData(line, argv[1]);
    }

    return 0;
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
        return "ERROR";
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
    strncat(buff, "\n", 128);
    strncat(line, buff, 128);

    free(buff);
    return line;
}

void AppendData(char* line, char* filename)
{
    int isFilePresent = 1;
    strcat(filename, ".txt");
    
    //Check if file exists
    if (fopen(filename, "r") == NULL)
        isFilePresent = 0;

    FILE* data = fopen(filename, "a+");
    if (!isFilePresent)
        fputs("*Cedula,Nombre,Apellido,Edad\n", data);    
    fputs(line, data);
}