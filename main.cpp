
#include <cstdlib>
#include <iostream>
#include <string>

#include "fsmClient.h"



typedef enum{NOEVENT,PUT,GET,QUIT} inputType;
#define ERROR -1
using namespace std;

inputType parseInput(string&); //devuelve el evento y en input el nombre del archivo

int main(int argc, char** argv)

{
    string input;
    inputType inputEvent=NOEVENT;
    
    fsmClient fsm;     
    
    if(fsm.connectClient())
    {
        cout << "se PUDO CONECTAR" << endl;
        do
        {                  
            do
            {
               getline(cin,input);
               inputEvent=parseInput(input); 
            }
            while(inputEvent==NOEVENT);   
        
            fsm.setFilename(input);  
    
    
            if(inputEvent==PUT)fsm.cicleFsm(wrq);
            else if(inputEvent==GET)fsm.cicleFsm(rrq);
            else if(inputEvent==QUIT) break; //ESTO ES HORRIBLE
             //nodelay(stdscr, TRUE);
            //fsm.initCurses();
             while(fsm.getCellState()!=FINISH)
            {        
                if(fsm.isEvent())
                fsm.cicleFsm(fsm.getEvent());
                if(fsm.isTimebreak())
                {
                    cout << "timeout papa";
                    fsm.cicleFsm(timebreak);        
                }
                /*if(fsm.isQuitPressed())
                 {
                    cout << "Se apreto Q";
                    fsm.cicleFsm(quit);
                }*/
            }
        //nodelay(stdscr,FALSE);
        cout << "fin trasmision archivo" << endl;
        fsm.reset();
        }
        while(inputEvent!=QUIT);
        cout << endl << "fin"; 
    }
    else 
    {
        cout << "NO SE PUDO CONECTAR" << endl;
        inputEvent==NOEVENT;
    } 
    }
   


inputType parseInput(string& input)
{
	size_t space=input.find(' ');
        size_t secondSpace;
	string aux;
        inputType event= NOEVENT;
        
	if(space!=input.npos)
	{
                aux=input.substr(0,space);                
		if(aux.compare("GET")==0) event=GET;
                else if(aux.compare("PUT")==0) event=PUT;
                else if(aux.compare("QUIT")==0) event=QUIT;
                else
                {
                    event= NOEVENT;
                    cout << endl <<"Invalid option";
                }
                if(event!=NOEVENT)
                {
                    secondSpace=input.find(' ',space+1);
                    input=input.substr(space+1,secondSpace-4);
                                                   
                }
	}
	else
	{
		cout << endl << "Invalid Input";
	}
        
        return event;
}