#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <tuple>

#include <search.h>

using namespace std;

#define ENTRY_TUPLE tuple<char*,char*,char*,char*>
#define TUPLE_LIST ENTRY_TUPLE*

int ProgramLoop(char* file);
TUPLE_LIST LoadData(char* data, char* file);
char* PromptUser();
void AppendData(char* line, char* filename);

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
    int quitflag = 0;
    while (!quitflag)
    {
        printf("Que quiere hacer?\n");
        printf("1. Registrar datos\n");
        printf("2. Listar todos los dato\n");
        printf("3. Buscar entrada\n");
        printf("Ponga cualquier pulse cualquier otra tecla para salir\n");
        char input = getch();

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
        default:
            break;
        }
    }
    return 0;
}

TUPLE_LIST LoadData(char* data, char* file)
{
    strcat(data, ".txt");
    FILE* dataFile = fopen(data, "r");
    if (dataFile == NULL)
    {
        printf_s("El archivo %s no existe\n",stderr);
        return (TUPLE_LIST)100;
    }
    
    char tmp;
    int entries = 0; //Starts at 0 because we know first line is a header 
    while ((tmp = fgetc(dataFile)) != EOF)
    {
        if (tmp == '\n')
            entries++;
    }
    rewind(dataFile);
    char* buff = (char*)malloc(entries);

    TUPLE_LIST lData = new ENTRY_TUPLE[entries];
    for (int i = 0; i < entries; i++)
        lData[i] = make_tuple((char*)0,(char*)0,(char*)0,(char*)0); //Initialize all tuples

    for (int i = 0; i < entries; ((tmp = fgetc(dataFile)) == '\n') ? i++ : 0)
    {
        
    }
    
    return (TUPLE_LIST)0;
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