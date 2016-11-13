

#ifndef INPUT_H
#define INPUT_H

#include <cstdlib>
#include <string>
#include <iostream>
#include <cstring>

using namespace std;

typedef enum{NOEVENT,PUT,GET,QUIT, HELP} inputType;
#define ERROR -1

typedef struct
{
    string IP;    
}paramType;

inputType parseInput(string& input);
int parseCallback (char *key, char *value, void *userData);
void* createUserData(void);
void destroyUserdata(void* userData);
bool checkParser (int);
 

#endif /* INPUT_H */

