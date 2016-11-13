
#include <cstdlib>
#include <iostream>
#include <string>
#include "input.h"
#include "parser.h"

#include "fsmClient.h"




using namespace std;



int main(int argc, char** argv)

{
    string input;
    inputType inputEvent=NOEVENT;
    fsmClient fsm;   
        if(fsm.connectClient())
        {
            cout << "Connection accepted" << endl;
            do
            {   
                cout << "Ready for transmition" << endl;
                do
                {
                    getline(cin,input);
                    inputEvent=parseInput(input); 
                }
                while(inputEvent==NOEVENT);   
        
                
    
                if(inputEvent==HELP)
                {
                    cout << "-GET filename- to read a file from server " << endl;
                    cout << "-PUT filename- to write a file to server" << endl;
                    cout << "-QUIT- to close client " << endl;
                
                }
                else
                {
                    if(inputEvent!=QUIT)
                    {
                        fsm.setFilename(input);
                        if(inputEvent==PUT)fsm.cicleFsm(wrq);
                        else if(inputEvent==GET)fsm.cicleFsm(rrq);
                        cout << "press Q to quit" << endl;
         
                        while(fsm.getCellState()!=FINISH)
                        {        
                            if(fsm.isEvent())
                                fsm.cicleFsm(fsm.getEvent());
                            if(fsm.isTimebreak())
                            {
                                fsm.cicleFsm(timebreak);        
                            }                            
                        }
                        
                        //cout << "End of transmition " << endl;
                        fsm.reset();
                    }
                }
            }
            while(inputEvent!=QUIT);
           cout << "Closing program " << endl;
        }
        else 
        {
             cout << "Could not connect to Server " << endl;       
        } 
    return 0;
}
   


