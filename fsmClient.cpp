#include "fsmClient.h"

fsmClient::fsmClient()
{
    cell.nextState=IDLE;
    cell.action=&fsmClient::nothing;
}

/*cellType fsmClient::getCell()
{
	return cell;
}*/


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
	clientServer.sendInfo(packet);    
     
}

void fsmClient::sendAck(void)
{
    //GUARDO LA INFO EN EL ARCHIVO
    p.createPacket(packet,ack,file.getChunkNum());
    clientServer.sendInfo(packet); 
   
}

void fsmClient::errorEvent(void)
{
    //ACA LOS ERRORES
   
}


void fsmClient::cicleFsm(typeEvent event)
{
    cell=fsm_matrix[cell.nextState][event];
    //cell.*((fsmClient*)this)->fsmClient::cellType::action();
    //cell.*(fsmClient::cellType::(fsmClient::action))();
    ((*this).*(cell.action))();
    timeAlert.feed_watchPuppy();
}

void fsmClient::sendData(void)
{
        //SI NUMERO ACK CORRESPONDE A NUMERO DATA
        file.increaseChunkNum();
	string dataString=file.getChunk();
	p.createPacket(packet,data,dataString,file.getChunkNum());
	clientServer.sendInfo(packet); 
}

bool fsmClient::isEvent()
{
    return clientServer.isEvent(packet);
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
}

bool fsmClient::isTimebreak()
{
    return timeAlert.watchPuppyAlert();
}
