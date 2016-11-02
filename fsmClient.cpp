#include "fsmClient.h"

fsmClient::fsmClient()
{
    cell.nextState=IDLE;
    cell.action=&fsmClient::nothing;
    //winTest=initscr();
    //cbreak();
    nodelay(stdscr, TRUE);
    noecho();      
}

fsmClient::~fsmClient()
{
    endwin();
}


void fsmClient::sendWrq()
{
        cout << "WRQ" << endl;
        file.openrFile(filename);//abrir archivo
	p.createPacket(packet,wrq,filename);
	clientServer.sendInfo(packet);
      
}

void fsmClient::sendRrq()
{
        cout << "RRQ" << endl;
        file.openwFile(filename);//abrir archivo
	p.createPacket(packet,rrq,filename);
	clientServer.sendInfo(packet); //VOLVER A PONER   
     
}

void fsmClient::sendAck(void)
{   
    string dataString;
    p.getPacketData(packet,dataString);
    file.chunkToFile(dataString);//GUARDO LA INFO EN EL ARCHIVO
    file.increaseChunkNum();
    p.createPacket(packet,ack,file.getChunkNum());
    clientServer.sendInfo(packet); //VOLVER APON ER
   
}

void fsmClient::errorEvent(void)
{
    //ACA LOS ERRORES
   
}


void fsmClient::cicleFsm(typeEvent event)
{
    cell=fsm_matrix[cell.nextState][event];
    ((*this).*(cell.action))();
    timeAlert.feed_watchPuppy();
}

void fsmClient::sendData(void)
{
        //SI NUMERO ACK CORRESPONDE A NUMERO DATA
        file.increaseChunkNum();
	string dataString=file.getChunk();
        if(file.End())
        {
            
            //cell=fsm_matrix[cell.nextState][last_data];
            p.createPacket(packet,data,dataString,file.getChunkNum());
            cout << "el paquete de data es: " << packet << endl;
            clientServer.sendInfo(packet); 
        }
        else
        {
            cout << "enviando DATA" << endl;
	p.createPacket(packet,data,dataString,file.getChunkNum());
	clientServer.sendInfo(packet); // VOLVER A PONER
        }
}

bool fsmClient::isEvent()
{
    return clientServer.isEvent(packet);
    //return false;
}

void fsmClient::setFilename(string& name)
{
    filename=name;
}

void fsmClient::nothing()
{
    
}

typeState fsmClient::getCellState(void)
{
    return cell.nextState;
}
        
typeEvent fsmClient::getEvent()
{
    return p.getPacketType(packet);
}

void fsmClient::end()
{
    //CIERRA EL ARCHIVO
    //Y HACES OTRAS COSAS
    file.closeFile();
    
    
    
}

bool fsmClient::isTimebreak()
{
    return timeAlert.watchPuppyAlert();
}

bool fsmClient::isQuitPressed()
{
    return (tolower(getch())=='q'); //ACA VA SI SE APRETO LA Q
}

bool fsmClient::connectClient()
{
    clientServer.doClientConnect();
    return clientServer.isConnect();
}