#include "input.h"
#include  "parser.h"
inputType parseInput(string& input)
{
	size_t space=input.find(' ');
        size_t secondSpace;
	string aux;
        inputType event= NOEVENT;
        if(input.compare("HELP")==0) return HELP;
        if(input.compare("QUIT")==0) return QUIT;
        
	if(space!=input.npos)
	{
                aux=input.substr(0,space);                
		if(aux.compare("GET")==0) event=GET;
                else if(aux.compare("PUT")==0) event=PUT;

                else
                {
                    event= NOEVENT;
                    cout <<"Invalid option" << endl;
                }
                if(event!=NOEVENT)
                {
                    secondSpace=input.find(' ',space+1);
                    input=input.substr(space+1,secondSpace-4);
                                                   
                }
	}
	else
	{
		cout << "Invalid Input"  << endl;
	}
        
        return event;
}

int parseCallback (char *key, char *value, void *userData){
    paramType *param=(paramType*)userData;
    int ret=1;
    if(key==NULL)
    {                      //es un parametro
        ret=0;        
    }
    else{                               //es una opcion
        if(!strcmp(key,"IP")){
            param->IP=string(value);         
        }
        
      /*el callback no checkea que los values tengan sentido practico*/
        else{
            ret=0;                      //key no valido
        }
    }
    return ret;
}

void* createUserData()
{
    return (void*)malloc(sizeof(paramType));
}

void destroyUserdata(void* userData)
{
    if(userData!=NULL);
    free(userData);
}

bool checkParser (int parser) {

	if(parser==SYNTAX_ERROR)
    {
        printf("Syntax error\n");        
        return false;
    }
    else if(parser==CALL_ERROR)
    {
        printf("Invalid parameter\n");
        return false;
    } 
	else 
		return true;

}