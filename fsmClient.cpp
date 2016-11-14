#include "fsmClient.h"

fsmClient::fsmClient()
{
    cell.nextState=IDLE;
    cell.action=&fsmClient::nothing;
      
}

fsmClient::~fsmClient()
{
    
}


void fsmClient::sendWrq()
{
        cout << "Sending " << filename << endl;
        if(file.openrFile(filename))
        {//abrir archivo
            p.createPacket(packet,wrq,filename);
            clientServer.sendInfo(packet);            
        }
        else
        {
            cell.nextState=FINISH;
            cout << "File not found" << endl;
        }
      
}

void fsmClient::sendRrq()
{

        cout << "Getting " << filename << endl;
        file.openwFile(filename);//abrir archivo
	p.createPacket(packet,rrq,filename);
	clientServer.sendInfo(packet); //VOLVER A PONER   
     
}

void fsmClient::sendAck(void)
{   
    if(p.getPacketBLock(packet)-1==file.getChunkNum())
    {
    string dataString;
    p.getPacketData(packet,dataString);
    file.chunkToFile(dataString);//GUARDO LA INFO EN EL ARCHIVO
    file.increaseChunkNum();
    p.createPacket(packet,ack,file.getChunkNum());
    clientServer.sendInfo(packet); //VOLVER APON ER
    if(dataString.length()<512)cicleFsm(quit);
    }
    else
    {
        cout << "packet y ack decincronizado" << endl;
        cicleFsm(error);
    }
}

void fsmClient::errorEvent(void)
{
    //ACA LOS ERRORES
    cout << "There was an error in the process " << endl;
    file.closeFile();
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
    cout << "packetblock "<<p.getPacketBLock(packet)<<endl;
    cout << "chunknum " <<file.getChunkNum()<<endl;
        if(p.getPacketBLock(packet)==file.getChunkNum())
        {
            file.increaseChunkNum();
            string dataString=file.getChunk();
            if(file.End())
            {            
                cout << "Sending last packet" << endl;
                cell.nextState=LAST_WRITE;
                p.createPacket(packet,data,dataString,file.getChunkNum());
                //cout << "el paquete de data es: " << packet << endl;
                clientServer.sendInfo(packet); 
            }
            else
            {
                //cout << "enviando DATA" << endl;
            p.createPacket(packet,data,dataString,file.getChunkNum());
            clientServer.sendInfo(packet); // VOLVER A PONER
            }
        }
        else
        {
            cout << "la fsm se fue a la bosta" << endl;
            cicleFsm(error);
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
    cout << "End of transmition" << endl;
    file.closeFile();
    
    
    
}

bool fsmClient::isTimebreak()
{
    return timeAlert.watchPuppyAlert();
}

/*bool fsmClient::isQuitPressed()
{
    return (tolower(getch())=='q'); //ACA VA SI SE APRETO LA Q
    //return getch();
}*/

bool fsmClient::connectClient()
{
    clientServer.doClientConnect();
    return clientServer.isConnect();
}

void fsmClient::resendPacket(void)
{
    clientServer.sendInfo(packet); 
}

/*void fsmClient::initCurses(void)
{
  nodelay(stdscr, TRUE); 
  noecho();
}*/

/*void fsmClient::closeCurses(void)
{
        nodelay(stdscr, FALSE);
        echo();
}*/

void fsmClient::reset()
{
    cell.nextState=IDLE;
    cell.action=&fsmClient::nothing;
}