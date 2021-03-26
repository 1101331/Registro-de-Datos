#ifndef _PROMPT_H_
#define _PROMPT_H_

int ProgramLoop(char* file);
char*** LoadData(char* file);
int CountEntries(char* file);
char* PromptUser();
void AppendData(char* line, char* filename);

#endif