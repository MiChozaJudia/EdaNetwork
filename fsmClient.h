
#ifndef FSMCLIENT_H
#define FSMCLIENT_H

#include <cstdlib>
#include <iostream>
#include <string>
#include "ncurses.h"
#include "packetManager.h"
#include "client.h"
#include "EventAndState.h"
#include "fileClass.h"
#include "watchPuppy.h"

#define STATE_COUNT 7
#define EVENT_COUNT 8





using namespace std;

class fsmClient
{
        typedef struct{
            typeState nextState;
            void (fsmClient::*action) (void);
	}cellType;
        

public:

	fsmClient();
	~fsmClient();
	void cicleFsm(typeEvent event);
	cellType getCell(void);
        typeState getCellState(void);
        bool isEvent();
        typeEvent getEvent();
        void setFilename(string& name);
        bool isTimebreak();
        bool isQuitPressed();

private:
        //WINDOW * winTest;
        string packet;
	cellType cell;
        string filename;
        watchPuppy timeAlert;
        fileClass file;        
        packetManager p;
        client clientServer; 
	const cellType fsm_matrix[STATE_COUNT][EVENT_COUNT]=
	{		
//wrq                               rrq                                 timebreak                            ack                                 quit                           last_data                           data                                error
{{FIRST_WRITE,&fsmClient::sendWrq}, {FIRST_READ,&fsmClient::sendRrq},	{IDLE,&fsmClient::nothing},         {IDLE,&fsmClient::nothing},         {FINISH,&fsmClient::end},       {IDLE,&fsmClient::nothing},         {IDLE,&fsmClient::nothing},         {FINISH,&fsmClient::errorEvent}},	//IDLE
{{FIRST_WRITE,&fsmClient::nothing}, {FIRST_WRITE,&fsmClient::nothing},	{FIRST_WRITE,&fsmClient::sendWrq},  {WRITE,&fsmClient::sendData},       {FINISH,&fsmClient::end},       {LAST_WRITE,&fsmClient::nothing},   {FIRST_WRITE,&fsmClient::nothing},  {FINISH,&fsmClient::errorEvent}},	//FIRST_WRITE
{{WRITE,&fsmClient::nothing},       {WRITE,&fsmClient::nothing},	{WRITE,&fsmClient::sendData},       {WRITE,&fsmClient::sendData},       {FINISH,&fsmClient::end},       {LAST_WRITE,&fsmClient::nothing},   {WRITE,&fsmClient::nothing},        {FINISH,&fsmClient::errorEvent}},	//WRITE
{{LAST_WRITE,&fsmClient::nothing},  {LAST_WRITE,&fsmClient::nothing},	{LAST_WRITE,&fsmClient::sendData},  {FINISH,&fsmClient::end},           {FINISH,&fsmClient::end},       {LAST_WRITE,&fsmClient::nothing},   {LAST_WRITE,&fsmClient::nothing},   {FINISH,&fsmClient::errorEvent}},	//LAST_WRITE
{{FIRST_READ,&fsmClient::nothing},  {FIRST_READ,&fsmClient::nothing},	{FIRST_READ,&fsmClient::sendRrq},   {FIRST_READ,&fsmClient::nothing},   {FINISH,&fsmClient::end},       {FINISH,&fsmClient::sendAck},       {READ,&fsmClient::sendAck},         {FINISH,&fsmClient::errorEvent}},	//FIRST_READ
{{READ,&fsmClient::nothing},        {READ,&fsmClient::nothing},		{READ,&fsmClient::sendAck},         {READ,&fsmClient::nothing},         {FINISH,&fsmClient::end},       {FINISH,&fsmClient::sendAck},       {READ,&fsmClient::sendAck},         {FINISH,&fsmClient::errorEvent}},	//READ
{{FINISH,&fsmClient::nothing},      {FINISH,&fsmClient::nothing},	{FINISH,&fsmClient::nothing},       {FINISH,&fsmClient::nothing},       {FINISH,&fsmClient::nothing},   {FINISH,&fsmClient::nothing},       {FINISH,&fsmClient::nothing},       {FINISH,&fsmClient::nothing}}           //FINISH
	};

	void sendWrq(void);
	void sendRrq(void);
	void end(void);
	void errorEvent(void);
	void sendData(void);
	void sendAck(void);	
	void nothing(void);
        
        
  

};

#endif /* FSMCLIENT_H */

