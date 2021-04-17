#ifndef _PROMPT_H_
#define _PROMPT_H_

int ProgramLoop(char* file);
char*** LoadData(char* file);
int CountEntries(char* file);
char* PromptUser();
void AppendData(char* line, char* filename);
void OverwriteData(char* file, char***lData, int entries);
void CharByChar(char* buff, char* conditions, char dispChar);

#endif