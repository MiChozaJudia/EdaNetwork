
#ifndef EVENTANDSTATE_H
#define EVENTANDSTATE_H

#ifdef __cplusplus
extern "C" {
#endif


//typedef enum {IDLE,FIRST_WRITE,FIRST_READ,WRITE,READ,LAST_WRITE,FINISH} typeState;
typedef enum {IDLE,FIRST_WRITE,WRITE,LAST_WRITE,FIRST_READ,READ,FINISH} typeState;
typedef enum {wrq,rrq,timebreak,ack,quit,last_data,data,error,no_event}	typeEvent;

#ifdef __cplusplus
}
#endif

#endif /* EVENTANDSTATE_H */

